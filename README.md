# 1811 Vehicle Software

> **Architecture note:** 1811 runs on **two on-board computers** — the Karbon 800
> (Ouster lidar + Arduino) and the Jetson Orin (4× ZED X cameras + most fusion/ROS
> work), joined by an Ethernet link into one ROS 2 graph. Read
> [`docs/compute_and_sensor_topology.md`](docs/compute_and_sensor_topology.md)
> before wiring up anything that consumes lidar and camera data together.

## Docker (this is how everything runs now — Karbon, Windows laptop, or any dev machine)

All ROS 2 code in this repo runs inside a Docker container built from `ros:humble`.
This means:

- **No native ROS 2 install is required on any machine** — not the Karbon
  (Ubuntu 24.04), not a Windows laptop (via WSL), not a fresh machine.
- The container brings its own Ubuntu 22.04 / ROS 2 Humble userspace
  regardless of what the host OS actually is. The host's job is just to run
  Docker.
- The same image and the same commands work identically everywhere. Machine
  differences (Karbon vs. laptop, Linux vs. WSL) only affect a couple of
  host-level steps below (USB passthrough, display forwarding) — never the
  ROS/Docker workflow itself.

### First-time setup (any machine)

```bash
git clone git@github.com:yourorg/1811.git
cd 1811
bash scripts/setup_machine.sh   # installs/checks Docker, builds the image
```

### Daily use

```bash
docker compose run --rm dev bash
```

This drops you into a shell **inside the container**, with:
- the repo bind-mounted at `/vehicle_1811` (edits on the host are reflected
  instantly, no rebuild needed),
- `/dev` passed through (so serial/USB devices appear exactly as they do on
  the host),
- your display forwarded (so the teleop pygame window can open).

ROS 2 and the workspace are sourced automatically when the container shell
starts. If you ever need to do it by hand (e.g. inside a script, or a shell
that skipped the automatic sourcing):

```bash
source /opt/ros/humble/setup.bash
source /vehicle_1811/ros2_ws/install/setup.bash
```

### Building the workspace after code changes

Same as before, just run **inside the container** now:

```bash
cd /vehicle_1811/ros2_ws
colcon build --symlink-install
source install/setup.bash
```

Run this again any time you edit C++ code, add/remove a package, or change
`package.xml` / `CMakeLists.txt`. Pure-Python changes take effect immediately
(no rebuild needed) as long as `--symlink-install` was used.

You do **not** need to rebuild the Docker image itself for code changes —
only for changes to system/apt/pip dependencies (i.e. edits to the
`Dockerfile`).

### docker-compose services

- **`dev`** — generic development container. Used on the Karbon, on laptops,
  anywhere. Bind-mounts the repo, passes through `/dev`, forwards `DISPLAY`.
- **`obc`** — same image, same setup, intended specifically for the Karbon
  running as the actual on-board computer. Exists as its own service mainly
  so Karbon-specific overrides (a fixed serial port path, autostart behavior,
  etc.) have somewhere to live later without touching the shared `dev`
  service.

`docker-compose.yml` (repo root):

```yaml
version: "3.8"
name: vehicle_1811
services:
  dev:
    build:
      context: .
      dockerfile: Dockerfile
    image: vehicle_1811
    container_name: vehicle_1811_dev_${USER}
    privileged: true
    stdin_open: true
    tty: true
    network_mode: "host"
    volumes:
      - type: bind
        source: $PWD
        target: /vehicle_1811
      - type: bind
        source: /dev
        target: /dev
      - type: bind
        source: /tmp/.X11-unix
        target: /tmp/.X11-unix
      - type: bind
        source: ${HOME}/.Xauthority
        target: /root/.Xauthority
    environment:
      - DISPLAY=${DISPLAY}
      - ROS_DOMAIN_ID=${ROS_DOMAIN_ID:-0}
      - RMW_IMPLEMENTATION=rmw_fastrtps_cpp

  obc:
    extends: dev
    container_name: vehicle_1811_obc
```

`privileged: true` gives the container full device access, which is why you
won't need to fuss with `dialout` group permissions *inside* the container —
it already has access to whatever the host exposes to it.

### Serial / USB devices inside the container

Because `/dev` is bind-mounted wholesale, `/dev/ttyACM0` (or whatever the
Arduino enumerates as) is visible inside the container exactly as it is on
the host — same name, same behavior.

- **On the Karbon:** plug in the Arduino, confirm the name with
  `ls /dev/ttyACM*` on the host, and it's already visible inside the
  container — no extra step.
- **On a Windows laptop (WSL):** you still need the `usbipd` steps below to
  get the device into WSL *first*. Docker Desktop's WSL2 backend only sees
  devices that WSL itself can see — it does not talk to Windows USB directly.
  Once `usbipd attach` succeeds and `ls /dev/ttyACM*` works from a plain WSL
  shell, it will also show up inside the container without any extra
  binding — the `/dev` bind-mount is live, not a snapshot, so devices that
  appear after the container has already started are picked up
  automatically (no need to restart `docker compose run`).

### GUI apps (teleop pygame window) inside the container

- **On the Karbon:** works via the standard X11 `DISPLAY` +
  `/tmp/.X11-unix` bind already wired into the compose file above.
- **On a Windows laptop (WSL):** requires WSLg (see WSL-specific setup
  below). Confirm `echo $DISPLAY` is non-empty in a **plain WSL shell**
  first — if it's empty there, it'll be empty inside the container too,
  since the container just inherits whatever `$DISPLAY` the host WSL shell
  had when you ran `docker compose run`.

---

## Running the Ouster lidar driver

The Ouster ROS 2 driver (`ouster_ros` / `ouster_sensor_msgs`) is vendored as a
git submodule at `ros2_ws/src/ouster-ros` (upstream `ros2` branch), not
hand-written code in this repo. After cloning or pulling changes that touch
it, fetch the submodule (and its own nested `ouster-sdk` submodule):

```bash
git submodule update --init --recursive
```

The image now includes the driver's build dependencies (`libeigen3-dev`,
`libjsoncpp-dev`, `libspdlog-dev`, `libcurl4-openssl-dev`, `libopencv-dev`,
`libzip-dev`, `libssl-dev`, `ros-humble-tf2-eigen`, `ros-humble-rviz2`), so a
normal workspace build picks it up:

```bash
cd /vehicle_1811/ros2_ws
colcon build --symlink-install
source install/setup.bash
```

`ouster_ros`'s `CMakeLists.txt` (and the nested `ouster-sdk`'s `ouster_client`)
`find_package(... REQUIRED)` for OpenCV, libzip, and OpenSSL — if any of those
three ever go missing again after a Dockerfile edit, colcon fails with a
`CMake Error` naming exactly which one, and `Dockerfile` needs the matching
apt package added back.

Connect to the sensor (host networking is already on via `docker-compose.yml`,
which the driver needs for UDP lidar/IMU packets):

```bash
ros2 launch ouster_ros sensor.launch.xml sensor_hostname:=<sensor-ip-or-hostname>
```

On a machine with no display attached (e.g. the Karbon with no monitor), pass
`viz:=false` — the launch file starts `rviz2` by default and it will crash
with "no Qt platform plugin could be initialized" if there's no X11 display:

```bash
ros2 launch ouster_ros sensor.launch.xml sensor_hostname:=<sensor-ip-or-hostname> viz:=false
```

This publishes point clouds to `/ouster/points` and IMU data to `/ouster/imu`.
Verify with:

```bash
ros2 topic hz /ouster/points
rviz2   # or: ros2 launch ouster_ros rviz.launch.xml
```

Note: `lidar_perception` (this repo's own package) has no source yet — it's
an empty skeleton. This driver is a separate, independent package; nothing in
`lidar_perception` consumes its output yet.

### UDP receive buffer warning

The driver logs `Failed to set desired SO_RCVBUF size to 1048576` if the
host's kernel UDP buffer ceiling is below 1 MB — this is a host `sysctl`
limit, not a container/driver issue (harmless at low data rates, but risks
dropped lidar packets under sustained load). Fix on the host:

```bash
sudo sysctl -w net.core.rmem_max=1048576
sudo sysctl -w net.core.rmem_default=1048576
```

To persist across reboots:

```bash
echo -e "net.core.rmem_max=1048576\nnet.core.rmem_default=1048576" | sudo tee /etc/sysctl.d/99-ouster.conf
sudo sysctl --system
```

## Serial protocol (Karbon <-> Arduino)

JSON, newline-terminated, **57600 baud**.

**Karbon -> Arduino:**
```json
{"speed": 2.500, "steering": -0.200, "braking": 0.000}
```
- `speed`: target speed in **mph** (not normalized — this is an actual speed value)
- `steering`: -1.0 .. 1.0
- `braking`: 0.0 .. 1.0

The Arduino currently does **not** send anything back — this link is command-only
for now.

## Running teleop (keyboard, no gamepad required)

Run all of the following **inside the Docker container**
(`docker compose run --rm dev bash`) — not directly on the host.

Requires a display: WSL users, confirm `echo $DISPLAY` is non-empty in a
plain WSL shell before entering the container (`wsl --update` / restart WSL
if empty — WSLg is required for the pygame window to appear).

**Terminal 1 — serial bridge** (each terminal enters its own container shell
via `docker compose run --rm dev bash`; ROS and the workspace are already
sourced automatically):
```bash
ros2 run teleop_bridge serial_bridge_node --ros-args -p port:=/dev/ttyACM0 -p baud:=57600
```
Check `ls /dev/ttyACM*` first — the device name can change between replugs.

**Terminal 2 — keyboard teleop:**
```bash
ros2 run teleop_bridge keyboard_teleop_node
```
Click into the pygame window (not the terminal) for it to receive keys.
- Arrows: drive (throttle / steer)
- Shift: brake (overrides throttle)
- +/-: adjust speed scale
- q / Esc: quit

**Terminal 3 (optional) — watch what's being published:**
```bash
ros2 topic echo /vehicle_command
```

## Running teleop (gamepad, once available)

```bash
ros2 launch teleop_bridge teleop_bridge.launch.py
```
Calibrate axis indices first — see comments at the top of
`teleop_bridge/gamepad_node.py`. Run `ros2 topic echo /joy` and move each
control individually to confirm which `axes[i]` maps to what before trusting
the defaults. The joystick device (e.g. `/dev/input/js0`) is passed through
the same way serial devices are — via the `/dev` bind-mount — so no extra
container config is needed once it shows up on the host.

## WSL-specific setup (if running on a laptop instead of the Karbon)

USB devices plugged into Windows aren't visible to WSL (or to Docker Desktop,
which runs on top of WSL) by default.

**Windows PowerShell (as Administrator):**
```powershell
winget install usbipd
usbipd list
usbipd bind --busid <busid>
usbipd attach --wsl --busid <busid>
```
Re-run `attach` after every unplug/replug or reboot.

**In a plain WSL shell**, confirm the device is visible *before* entering the
container:
```bash
ls /dev/ttyACM* /dev/ttyUSB*
```

Once that shows the device, it will also be visible inside
`docker compose run --rm dev bash` automatically.

Also confirm Docker Desktop's WSL integration is enabled for your distro:
**Docker Desktop → Settings → Resources → WSL Integration** — toggle your
distro on, then **Apply & Restart** if you change it.

## Setting up on the Karbon (or any fresh machine)

```bash
git clone git@github.com:yourorg/1811.git
cd 1811
bash scripts/setup_machine.sh
docker compose run --rm dev bash
```

No native ROS 2 install is needed anywhere in this flow. `scripts/setup_machine.sh`
only handles host-level prerequisites (Docker itself, plus a couple of
convenience/fallback steps) — see the script for details.

## Known issues / things to watch

- **No watchdog on the Arduino yet.** If the serial link goes stale, the
  firmware currently keeps executing the last received command indefinitely.
  `checkStaleness()` exists in the firmware but must be enabled, and should
  set `braking = 1.0` (not 0) on timeout. **Do not run this vehicle
  unsupervised or with wheels on the ground until this is fixed.** This is a
  firmware-level issue and applies identically whether the ROS side is
  running natively or inside Docker.
- Debug `Serial.println()` calls in the firmware were removed — they were
  polluting the same serial channel the Python side parses as JSON, causing
  intermittent parse failures.
- The firmware only drains one line from the serial buffer per `loop()`
  iteration in earlier versions — if commands start lagging/backing up
  again, check that the drain-all-buffered-lines fix is still in place.
- If a device (`/dev/ttyACM0`, `/dev/input/js0`, etc.) doesn't appear inside
  a container that's already running, it usually means the device wasn't
  present on the host yet when checked — re-run `ls /dev/ttyACM*` on the
  host first; the container's `/dev` bind-mount reflects the host live, so
  there's no need to restart the container once the device is actually there.
- **Ouster driver crashes with `terminate called after throwing an instance
  of 'std::out_of_range'` / `Field 'WINDOW' not found in LidarScan` on
  sensors running firmware older than 3.2.0.** The driver's point-cloud field
  layout for the `RNG19_RFL8_SIG16_NIR16` profile always includes a `WINDOW`
  (window-blockage) field, but that field doesn't exist in the sensor's
  actual data below firmware 3.2 — this happens regardless of which
  `point_type` is selected, since the field layout is chosen by
  `udp_profile_lidar`, not `point_type`. Our unit at the Karbon is on
  firmware 3.0.1 and hits this. Two options: upgrade the sensor firmware to
  3.2+ (real fix), or add `udp_profile_lidar:=LEGACY` to the launch command
  as a workaround — the `LEGACY` profile's field layout doesn't reference
  `WINDOW` and is supported by all firmware versions, at the cost of losing
  the newer profile's ambient/reflectivity encoding.