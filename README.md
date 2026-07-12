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

Requires a display (WSL: confirm with `echo $DISPLAY`, and `wsl --update` /
restart WSL if empty — WSLg is required for the pygame window to appear).

**Terminal 1 — serial bridge:**
```bash
source ~/1811/ros2_ws/install/setup.bash
ros2 run teleop_bridge serial_bridge_node --ros-args -p port:=/dev/ttyACM0 -p baud:=57600
```
Check `ls /dev/ttyACM*` first — the device name can change between replugs.

**Terminal 2 — keyboard teleop:**
```bash
source ~/1811/ros2_ws/install/setup.bash
ros2 run teleop_bridge keyboard_teleop_node
```
Click into the pygame window (not the terminal) for it to receive keys.
- Arrows: drive (throttle / steer)
- Shift: brake (overrides throttle)
- +/-: adjust speed scale
- q / Esc: quit

**Terminal 3 (optional) — watch what's being published:**
```bash
source ~/1811/ros2_ws/install/setup.bash
ros2 topic echo /vehicle_command
```

## Running teleop (gamepad, once available)

```bash
ros2 launch teleop_bridge teleop_bridge.launch.py
```
Calibrate axis indices first — see comments at the top of
`teleop_bridge/gamepad_node.py`. Run `ros2 topic echo /joy` and move each
control individually to confirm which `axes[i]` maps to what before trusting
the defaults.

## WSL-specific setup (if running on a laptop instead of the Karbon)

USB devices plugged into Windows aren't visible to WSL by default.

**Windows PowerShell (as Administrator):**
```powershell
winget install usbipd
usbipd list
usbipd bind --busid <busid>
usbipd attach --wsl --busid <busid>
```
Re-run `attach` after every unplug/replug or reboot.

**In WSL**, confirm:
```bash
ls /dev/ttyACM* /dev/ttyUSB*
```

## Setting up on the Karbon (or a fresh machine)

```bash
git clone git@github.com:yourorg/1811.git
cd 1811
bash scripts/setup_karbon.sh
source ~/1811/ros2_ws/install/setup.bash
```

## Known issues / things to watch

- **No watchdog on the Arduino yet.** If the serial link goes stale, the
  firmware currently keeps executing the last received command indefinitely.
  `checkStaleness()` exists in the firmware but must be enabled, and should
  set `braking = 1.0` (not 0) on timeout. **Do not run this vehicle
  unsupervised or with wheels on the ground until this is fixed.**
- Debug `Serial.println()` calls in the firmware were removed — they were
  polluting the same serial channel the Python side parses as JSON, causing
  intermittent parse failures.
- The firmware only drains one line from the serial buffer per `loop()`
  iteration in earlier versions — if commands start lagging/backing up
  again, check that the drain-all-buffered-lines fix is still in place.
EOF
## Running the setup script on a new machine

Once ROS 2 Humble is installed and the repo is cloned:

```bash
cd ~/1811
bash scripts/setup_karbon.sh
```

If it says it added you to the `dialout` group, log out and back in (or
close/reopen your terminal) before running any serial commands, then:

```bash
source ~/1811/ros2_ws/install/setup.bash
```
