# 1811 Vehicle Software

ROS 2 Humble stack for the 1811 vehicle, running entirely in Docker.

> **Architecture:** 1811 runs on **two on-board computers** — the Karbon 800
> (Ouster lidar + Arduino) and the Jetson Orin (4× ZED X cameras + most
> fusion work), joined by Ethernet into one ROS 2 graph. Read
> [`docs/compute_and_sensor_topology.md`](docs/compute_and_sensor_topology.md)
> before wiring up anything that consumes lidar and camera data together.

**Before driving:** [Safety](#safety) — there is no watchdog and no deadman
switch. A human on the kill switch is the only backstop that exists.

---

## Contents

- [Quick reference](#quick-reference) — topics, nodes, what's built
- [Setup](#setup) — first time, on any machine
- [Daily use](#daily-use) — enter the container, build
- [Workflows](#workflows) — copy-paste command blocks
  - [Manual teleop — gamepad](#manual-teleop--gamepad)
  - [Manual teleop — keyboard](#manual-teleop--keyboard)
  - [Lidar + odometry](#lidar--odometry)
  - [Teach and repeat](#teach-and-repeat)
- [Troubleshooting](#troubleshooting) — symptom → cause → fix
- [Safety](#safety) and [Known issues](#known-issues)
- [Machine-specific setup](#machine-specific-setup) — WSL, Karbon

---

## Quick reference

### Data flow

```
                gamepad_node ─┐
                              ├─> /vehicle_command ─> serial_bridge_node ─> Arduino
           pure_pursuit_node ─┘        (VehicleCommand)
                    ^
                    │ /odometry
  Ouster ─> /ouster/points ─> localization (KISS-ICP) ─┬─> route_recorder_node ─> route CSV
                                                       └─> pure_pursuit_node
```

**Only `serial_bridge_node` ever opens the serial port.** If the wheels don't
turn, it is the first thing to check — no other node can move the vehicle.

### Topics

| Topic | Type | Published by | Consumed by |
|---|---|---|---|
| `/joy` | `sensor_msgs/Joy` | `joy_node` | `gamepad_node` |
| `/vehicle_command` | `vehicle_msgs/VehicleCommand` | `gamepad_node`, `keyboard_teleop_node`, `pure_pursuit_node`\* | `serial_bridge_node` |
| `/vehicle_state` | `vehicle_msgs/VehicleState` | `serial_bridge_node` | — (firmware sends nothing back yet) |
| `/cmd/auto` | `vehicle_msgs/VehicleCommand` | `pure_pursuit_node` (default) | — (`mode_manager` not built) |
| `/ouster/points` | `sensor_msgs/PointCloud2` | `ouster_ros` | `localization` |
| `/odometry` | `nav_msgs/Odometry` | `localization` (KISS-ICP) | `route_recorder_node`, `pure_pursuit_node` |

\* only when launched with `cmd_topic:=/vehicle_command` — see
[Teach and repeat](#teach-and-repeat).

### Packages

| Package | What it does | Status |
|---|---|---|
| `teleop_bridge` | `gamepad_node`, `keyboard_teleop_node`, `serial_bridge_node` | ✅ |
| `localization` | Lidar odometry, wraps KISS-ICP → `/odometry` | ✅ |
| `routing` | `route_recorder_node` — record a route while driving | ✅ |
| `control` | `pure_pursuit_node`, `bicycle_sim_node` | ✅ |
| `vehicle_msgs` | `VehicleCommand`, `VehicleState`, `Detection` | ✅ |
| `vehicle_1811_description` | URDF, frames (`base_link` → `os_sensor` → `os_lidar`) | ✅ |
| `ouster-ros` | Vendored Ouster driver (git submodule) | ✅ |
| `routing` → `route_publisher` | Saved route → live `/planning/path` | ❌ not built |
| `guardian` → `mode_manager` | Manual/auto arbitration + deadman | ❌ not built |
| `lidar_perception`, `camera_perception`, `sensor_fusion` | — | ❌ empty skeletons |

Each package has its own README with the details:
[`control`](ros2_ws/src/control/README.md),
[`routing`](ros2_ws/src/routing/README.md),
[`localization`](ros2_ws/src/localization/README.md),
[`vehicle_1811_description`](ros2_ws/src/vehicle_1811_description/README.md).

---

## Setup

Everything runs inside a Docker container built from `ros:humble`. **No native
ROS 2 install is needed on any machine** — not the Karbon (Ubuntu 24.04), not a
Windows laptop (via WSL). The container brings its own Ubuntu 22.04 / Humble
userspace; the host just runs Docker.

```bash
git clone git@github.com:yourorg/1811.git
cd 1811
git submodule update --init --recursive
bash scripts/setup_machine.sh
```

`setup_machine.sh` handles host-level prerequisites (Docker itself) and builds
the image. The submodule step fetches `ouster-ros` and its nested `ouster-sdk`.

On WSL, do the [usbipd steps](#wsl-windows-laptop) before expecting any USB
device to show up.

---

## Daily use

Start the container once:

```bash
docker compose up -d dev
```

Then open a shell in it — **once per terminal you need**:

```bash
docker compose exec dev bash
```

> **Prefer `exec` over `run` for extra terminals.** Each `docker compose run`
> creates a *separate container*, and separate containers are what make DDS
> participant GUIDs collide (see [Known issues](#known-issues)). One container
> with many `exec` shells has one PID space and one DDS participant pool — and
> it starts faster. `docker compose run --rm dev bash` still works for a
> throwaway one-off.

That's the whole thing — **no `cd`, no `source`.** Every shell opens already
`cd`'d into `/vehicle_1811/ros2_ws` with ROS 2 *and* the built workspace overlay
sourced, so `ros2 launch ...` works on the first line you type. The repo is
bind-mounted at `/vehicle_1811`, `/dev` is passed through, and `DISPLAY` is
forwarded.

If the workspace hasn't been built yet, the shell says so on open instead of
failing later with a confusing "package not found."

Build after code changes — there's an alias for it:

```bash
rebuild
```

That expands to `colcon build --symlink-install && source install/setup.bash`.
When you only touched one or two packages, skip the alias and select them:

```bash
colcon build --symlink-install --packages-select control routing teleop_bridge && source install/setup.bash
```

- Pure-Python edits take effect immediately with `--symlink-install` — no rebuild.
- Rebuild for C++ changes, new/removed packages, or `package.xml` / `CMakeLists.txt` edits.
- Rebuild the **Docker image** only for `Dockerfile` changes (apt/pip deps, or the
  shell setup above):
  ```bash
  docker compose build
  ```

---

## Workflows

Every command below runs **inside the container**. Each numbered terminal is its
own `docker compose exec dev bash` — see [Daily use](#daily-use) for why `exec`
rather than a fresh `run` container per terminal.

### Manual teleop — gamepad

One command starts `joy_node`, `gamepad_node`, and `serial_bridge_node`:

```bash
ros2 launch teleop_bridge teleop_bridge.launch.py
```

The serial port is auto-detected via `/dev/serial/by-id/`. To override:

```bash
ros2 launch teleop_bridge teleop_bridge.launch.py port:=/dev/ttyACM0
```

Controls — 8BitDo SN30 Pro, **wired**, measured on this pad:

| Axis | Control | Sign | Used as |
|---|---|---|---|
| `axes[0]` | left stick X | right = **negative** | — |
| `axes[1]` | left stick Y | up = **positive** | throttle |
| `axes[2]` | left trigger | rests **+1.0**, → −1.0 pressed | brake |
| `axes[3]` | right stick X | right = **negative** | steering |
| `axes[4]` | right stick Y | up = **positive** | — |

`INVERT_STEER = True` because right reads negative on `axes[3]`; `INVERT_THROTTLE
= False` because up already reads positive on `axes[1]`.

**Axis numbers depend on the pad's mode, which is selected by a button combo at
power-on — not by the cable.** Over Bluetooth this pad reported steering on
`axes[2]` and the trigger on `axes[5]`. Re-verify after any power-cycle into
another mode, a pad swap, or a repair:

```bash
ros2 topic echo /joy
```

Move one control at a time and confirm against the table above and the constants
in [`gamepad_node.py`](ros2_ws/src/teleop_bridge/teleop_bridge/gamepad_node.py).
`gamepad_node` refuses to publish (and logs why) if `/joy` arrives with fewer
axes than it reads, rather than dying mid-drive.

### Manual teleop — keyboard

**Terminal 1** — serial bridge:

```bash
ros2 launch teleop_bridge teleop_bridge.launch.py use_gamepad:=false
```

**Terminal 2** — keyboard teleop:

```bash
ros2 run teleop_bridge keyboard_teleop_node
```

Click into the **pygame window** (not the terminal) for it to receive keys.
Arrows drive, Shift brakes (overrides throttle), `+`/`-` adjust speed scale,
`q`/`Esc` quits. Requires a display — see [GUI apps](#gui-apps-pygame-window).

### Lidar + odometry

**Terminal 1** — Ouster driver. `viz:=false` matters on the Karbon (no monitor;
`rviz2` crashes without X11). `udp_profile_lidar:=LEGACY` works around the
firmware 3.0.1 bug — see [Known issues](#known-issues):

```bash
ros2 launch ouster_ros sensor.launch.xml sensor_hostname:=<sensor-ip> viz:=false udp_profile_lidar:=LEGACY
```

**Terminal 2** — odometry:

```bash
ros2 launch localization localization.launch.py
```

Verify:

```bash
ros2 topic hz /odometry
```

### Teach and repeat

Drive a loop by hand while lidar odometry records it, then drive it back
autonomously.

> **⚠️ Read [Safety](#safety) before the REPEAT step.** There is no watchdog
> and no deadman switch. Also see [Known issues](#known-issues) — the goal check
> currently trips immediately on a closed loop, so REPEAT does not yet work on a
> route that ends where it started.

**Terminal 1** — lidar:

```bash
ros2 launch ouster_ros sensor.launch.xml sensor_hostname:=<sensor-ip> viz:=false udp_profile_lidar:=LEGACY
```

**Terminal 2** — odometry. **Do not restart this until REPEAT is completely
done.** Restarting moves the `odom` frame origin and the recorded route
silently stops matching reality, with no error:

```bash
ros2 launch localization localization.launch.py
```

**Terminal 3** — start recording:

```bash
ros2 launch routing route_recorder.launch.py
```

**Terminal 4** — TEACH: drive the loop by hand. `route_recorder_node` only
*listens* to `/odometry`; it does not move anything:

```bash
ros2 launch teleop_bridge teleop_bridge.launch.py
```

Drive the loop, back to your starting spot.

**Terminal 3** — save the route. Prints the file path you need next:

```bash
ros2 service call /route_recorder_node/save std_srvs/srv/Trigger {}
```

**Terminal 4** — now `Ctrl-C` the gamepad teleop and restart it **without the
gamepad**, so nothing competes with `pure_pursuit_node` for `/vehicle_command`:

```bash
ros2 launch teleop_bridge teleop_bridge.launch.py use_gamepad:=false
```

**Terminal 5** — REPEAT, dry run first. Default `cmd_topic` is `/cmd/auto`,
which nothing subscribes to — **nothing moves**, this is pure observation:

```bash
ros2 launch control pure_pursuit.launch.py path_file:=/vehicle_1811/routes/route_<timestamp>.csv
```

**Terminal 6** — watch the output. Push the car by hand and confirm the steer
and throttle values track sensibly:

```bash
ros2 topic echo /cmd/auto
```

**Terminal 5** — REPEAT for real, only once the above looks right *and* you've
read [Safety](#safety). This sends straight to the Arduino:

```bash
ros2 launch control pure_pursuit.launch.py cmd_topic:=/vehicle_command path_file:=/vehicle_1811/routes/route_<timestamp>.csv
```

See [`control`'s README](ros2_ws/src/control/README.md), "Bench test through
serial_bridge," for the full pre-flight checklist.

**No hardware at all?** `pure_pursuit_node` runs closed-loop against a
simulated bicycle model, using the bundled sample route:

```bash
ros2 launch control pure_pursuit.launch.py use_sim:=true
```

---

## Troubleshooting

### The vehicle doesn't move, but `/vehicle_command` echoes fine

The graph is healthy and the break is at the serial leg. Check that anything is
actually subscribed:

```bash
ros2 topic info /vehicle_command --verbose
```

Subscriber count `0` means `serial_bridge_node` is dead or never started. Under
`ros2 launch`, a node that dies at startup prints one `process has died` line
that scrolls past while the others keep running — everything *looks* alive.
Confirm:

```bash
ros2 node list
```

`serial_bridge_node` logs the port it opened at startup, and logs
`SERIAL BRIDGE DID NOT START` (with the available devices listed) if it
couldn't. Check the host's view of the devices:

```bash
ls -l /dev/serial/by-id/
```

### Throttle is always 0 in `/vehicle_command`

The brake trigger is being read as pressed. If `TRIGGER_RESTS_AT_PLUS_ONE` in
[`gamepad_node.py`](ros2_ws/src/teleop_bridge/teleop_bridge/gamepad_node.py) is
wrong for your connection, brake sits at ~0.5 at rest and throttle is forced to
0 forever — the topic still publishes, so it looks fine. Echo `/joy`, read the
trigger axis **at rest**, and set the constant to match.

### `pure_pursuit_node` says "Goal reached" immediately

Expected, today, for any route that ends near where it started — see
[Known issues](#known-issues).

### Nodes can't see each other across containers

All containers must agree on `ROS_DOMAIN_ID` (hardcoded to `0` in
`docker-compose.yml`) and use `network_mode: host`. Check:

```bash
ros2 topic list
```

Note `docker-compose.yml` sets `FASTRTPS_DEFAULT_PROFILES_FILE` to
`/vehicle_1811/config/fastdds_cable.xml`, **but no `config/` directory exists in
this repo.** Fast DDS falls back to defaults when the file is missing, so this
is currently harmless — but if that file is ever added with a transport
whitelist, it will silently break same-host discovery.

### A device doesn't appear inside the container

The `/dev` bind-mount reflects the host **live** — devices that appear after the
container started are picked up automatically, no restart needed. So if it's not
there, it wasn't on the host either. Check on the host first, and on WSL re-run
`usbipd attach` (it does not survive a replug or reboot).

---

## Safety

Autonomous driving today has **no automatic backstop of any kind**:

- **No firmware watchdog.** `checkStaleness()` exists in the Arduino code but
  isn't enabled. If the command stream stops for *any* reason —
  `pure_pursuit_node` crashing, `serial_bridge_node` dying, a network hiccup —
  the firmware keeps executing the **last command it received, forever**. It
  does not brake on its own.
- **No `mode_manager`, no deadman switch.** Nothing requires a held button to
  keep the vehicle driving, and nothing arbitrates manual vs. autonomous
  commands. That's why REPEAT wants `use_gamepad:=false` — two publishers on
  `/vehicle_command` means the Arduino acts on whichever message landed last.
- `pure_pursuit_node`'s internal safety net (zero throttle if the path hasn't
  loaded or `/odometry` goes stale) covers *only those two failures*, and only
  while the node is still alive. It cannot help if the process dies outright or
  the link to `serial_bridge_node` breaks.

**A human at the kill switch is the only thing standing in for the missing
watchdog and deadman.** Treat every REPEAT run as "manual driving with a robot
doing the steering," never as something to walk away from. Wheels off the
ground for the first run of anything new; spotter present; start slow.

---

## Known issues

- **UNRESOLVED: steering went to full lock and stayed there during a TEACH run.**
  Running `teleop_bridge.launch.py` + `route_recorder.launch.py` only (no
  `pure_pursuit_node`), the wheels commanded hard right without the stick being
  touched, and stayed there. Ruled out since: `route_recorder_node` has no
  publishers and cannot command anything; `pure_pursuit_node` was not running;
  the gamepad axis mapping was re-measured afterward and is correct. The
  *sticking* is explained — with no firmware watchdog, the Arduino holds the last
  command forever, so anything that stops the `/vehicle_command` stream freezes
  the wheels wherever they were. What produced the full-lock value in the first
  place is still unknown, but it happened **both times moments after
  `route_recorder.launch.py` was started in another container** — see the DDS
  GUID collision entry below, which is the leading hypothesis. Other leads not
  yet checked: whether the pad was in a different power-on mode during that run,
  `joy_node` behavior on device disconnect/reconnect, and stick drift.
  `serial_bridge_node` now clamps to ±1 and logs any out-of-range command, so a
  repeat should leave evidence in the log.
- **DDS participant GUID collisions across containers** (leading suspect for the
  entry above). Fast DDS derives a participant's GUID prefix from a host
  identifier plus the process id. `network_mode: host` and `ipc: host` already
  make the host part identical across containers, and without a shared PID
  namespace each `docker compose run` container numbers processes from 1 — so
  two containers readily produce the same pid, hence the same GUID prefix.
  Duplicate GUIDs are undefined behavior in DDS: discovery mis-attributes
  endpoints and a reader can be matched to a writer on a different topic, which
  would deliver bytes that were never a `VehicleCommand` into one — arbitrary
  floats, easily outside ±1. Consistent with both the out-of-range steering and
  with topics intermittently not crossing containers. **Mitigated** by `pid:
  "host"` in `docker-compose.yml` (host pids are unique) and by using one
  container with `docker compose exec` shells instead of many `run` containers.
  Unconfirmed — see the falsifiable test in that entry.
- **`pure_pursuit_node` trips its goal check immediately on a closed loop.**
  The check measures straight-line distance to the *last* waypoint with no
  notion of progress along the path, so a route ending within `goal_tolerance`
  (0.3 m) of its start reports "Goal reached" on the first control tick, before
  moving. **This defeats teach-and-repeat by design** — a taught loop returns
  to its start. Fix is to gate the goal on path progress (`_last_idx` near the
  end), not just proximity. See
  [`pure_pursuit_node.py:156`](ros2_ws/src/control/control/pure_pursuit_node.py:156).
- **Speed limits disagree.** `control/config/pure_pursuit.yaml` sets
  `max_speed_mps: 2.2352` (5 mph) with a comment saying it *must* match
  `serial_bridge_node`'s `MAX_SPEED_MPH` — which is **12.5**. Reconcile these
  before an autonomous run; the throttle scaling depends on it.
- **No watchdog on the Arduino.** See [Safety](#safety). Must be enabled and
  should set `braking = 1.0` (not 0) on timeout.
- **Ouster driver crashes on sensor firmware < 3.2.0** with
  `std::out_of_range` / `Field 'WINDOW' not found in LidarScan`. The driver's
  field layout for `RNG19_RFL8_SIG16_NIR16` always includes a `WINDOW` field
  that doesn't exist below firmware 3.2 — regardless of `point_type`, since the
  layout follows `udp_profile_lidar`. Our unit is on 3.0.1. Either upgrade the
  sensor firmware (real fix) or pass `udp_profile_lidar:=LEGACY` (workaround,
  costs the newer profile's ambient/reflectivity encoding).
- **`Failed to set desired SO_RCVBUF size`** from the Ouster driver means the
  host's UDP buffer ceiling is under 1 MB. Harmless at low rates, risks dropped
  packets under load. Fix on the **host**, not in the container:
  ```bash
  echo -e "net.core.rmem_max=1048576\nnet.core.rmem_default=1048576" | sudo tee /etc/sysctl.d/99-ouster.conf && sudo sysctl --system
  ```
- Debug `Serial.println()` calls were removed from the firmware — they polluted
  the same channel the Python side parses as JSON, causing intermittent parse
  failures.
- Earlier firmware drained only one serial line per `loop()`. If commands start
  lagging or backing up, check the drain-all-buffered-lines fix is still there.

---

## Serial protocol (Karbon ↔ Arduino)

JSON, newline-terminated, **57600 baud**.

**Karbon → Arduino:**

```json
{"speed": 2.500, "steering": -0.200, "braking": 0.000}
```

- `speed` — target speed in **mph** (an actual speed, not normalized).
  `serial_bridge_node` computes it as `throttle × MAX_SPEED_MPH`.
- `steering` — `-1.0` … `1.0`
- `braking` — `0.0` … `1.0`

`serial_bridge_node` clamps `throttle`/`steer` to ±1 and `brake` to 0…1 before
writing, and logs a throttled warning naming the offending value when it has to.
It is the last thing between a bad command and the hardware, so these ranges are
enforced there rather than trusted from upstream.

The Arduino currently sends **nothing back**; this link is command-only.
`serial_bridge_node` parses replies defensively anyway, so enabling telemetry
later won't require changes on the ROS side.

---

## Machine-specific setup

### GUI apps (pygame window)

- **Karbon:** works via the X11 `DISPLAY` + `/tmp/.X11-unix` bind already in
  `docker-compose.yml`.
- **WSL:** requires WSLg. Confirm `echo $DISPLAY` is non-empty in a **plain WSL
  shell** first — the container inherits whatever `$DISPLAY` the host shell had
  when you ran `docker compose run`. If it's empty there, it's empty inside.

### WSL (Windows laptop)

USB devices plugged into Windows aren't visible to WSL — or to Docker Desktop,
which runs on top of WSL — by default. Docker Desktop's WSL2 backend only sees
what WSL itself sees; it does not talk to Windows USB directly.

**Windows PowerShell (as Administrator):**

```powershell
winget install usbipd
usbipd list
usbipd bind --busid <busid>
usbipd attach --wsl --busid <busid>
```

Re-run `attach` after **every** unplug/replug or reboot.

**In a plain WSL shell**, confirm before entering the container:

```bash
ls -l /dev/serial/by-id/ /dev/input/js*
```

Also enable **Docker Desktop → Settings → Resources → WSL Integration** for your
distro, then **Apply & Restart**.

### docker-compose services

- **`dev`** — generic development container. Used everywhere.
- **`obc`** — same image and setup, intended for the Karbon as the actual
  on-board computer. Exists as its own service so Karbon-specific overrides
  (fixed serial path, autostart) have somewhere to live without touching `dev`.

`privileged: true` gives full device access, which is why you don't need to
fuss with `dialout` group permissions inside the container.
