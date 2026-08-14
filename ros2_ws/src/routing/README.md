# routing

`route_recorder_node`: the TEACH half of teach-and-repeat. Subscribes
`/odometry`, downsamples it into waypoints, and saves a CSV that
`control`'s `pure_pursuit_node` can load directly. This is **step A1** of
the teach-and-repeat milestone — see
[`docs/teach_and_repeat_guide.md`](../../../docs/teach_and_repeat_guide.md#stage-a1--record--replay-the-route--day-3).

`route_publisher` (the other half of A1, which would publish a recorded
route as a latched `nav_msgs/Path` on `/planning/path`) isn't built yet —
not needed for a first teach-and-repeat cycle, since `pure_pursuit_node`
can already load a CSV directly via its `path_file` param. Build it when
you actually need the `/planning/path` pipeline (e.g. a `route_publisher`
that swaps routes without restarting `pure_pursuit_node`).

## Contract

| | |
|---|---|
| **Subscribes** | `/odometry` (`nav_msgs/Odometry`) — live pose |
| **Services** | `~/start_recording`, `~/stop_recording`, `~/save` (all `std_srvs/Trigger`) |
| **Writes** | a CSV file: `x,y,yaw` per row — the exact format `control.pure_pursuit_core.load_csv_path` expects |
| **Does not publish** | anything — this is a file-writer, not a topic producer. (`route_publisher`, not built, would be the one that turns a saved file back into a ROS topic.) |

## ⚠️ Must run in the same odometry session you intend to repeat in

This node just appends whatever `/odometry` reports. It has no idea whether
that frame is trustworthy across a restart — **you do**. Restarting
`localization` between recording and replaying moves the `odom` frame's
origin, and the saved route silently stops matching where the vehicle
actually is (no error, no crash — it just quietly drives wrong). Don't kill
`localization` between TEACH and REPEAT. See the guide's "map is a
coordinate system, not a destination" section for why.

## Why `/vehicle_1811/routes`, and where it actually lands

That path is inside the repo, which `docker-compose.yml` already
bind-mounts (`$PWD` on the host → `/vehicle_1811` in the container) — so
routes saved there are visible on the Karbon's host filesystem too, with no
extra mount needed. It's excluded via `/routes/` in the repo's
`.gitignore`, since recorded driving data isn't source and shouldn't end up
in a commit. If you'd rather keep routes somewhere outside the repo
entirely (e.g. so they survive a `git clean`), that needs a matching bind
mount added to `docker-compose.yml` first — paths that aren't
`/vehicle_1811/...`, `/dev`, or the X11 sockets don't exist on both sides
of the container boundary.

**The directory doesn't exist until you've actually recorded something** —
`route_recorder_node` creates it on first use (`os.makedirs`), it's not
shipped in the repo. Once it exists:
- **Inside the container:** `/vehicle_1811/routes/`
- **On the Karbon's host:** the `routes/` subdirectory of whatever
  directory you ran `docker compose run` *from* — `$PWD` is captured at
  that moment, so it's `<wherever you launched docker compose>/routes/`,
  in practice wherever this repo is cloned on the Karbon (next to its own
  `docker-compose.yml`).

### Viewing a saved route

From inside the container (any terminal in the same `docker compose run`
session, or a fresh `docker compose exec dev bash` into the running one):

```bash
ls -la /vehicle_1811/routes                              # list saved routes, newest last
cat /vehicle_1811/routes/route_20260814_103000.csv        # dump one route's waypoints
```

It's a plain CSV (`x,y,yaw` per row, see "Contract" above), so anything that
reads CSV works too — `column -s, -t < route_....csv` for aligned columns,
or load it with pandas/Excel on the host copy (same file, no extra step,
since `/vehicle_1811/routes` is the bind-mounted `routes/` dir above). No
special ROS tooling needed to just look at one.

## A full teach-and-repeat cycle, today (no mode_manager, no route_publisher)

```bash
docker compose run --rm dev bash
cd /vehicle_1811/ros2_ws
colcon build --packages-select routing control
source install/setup.bash

# terminal 1 -- lidar
ros2 launch ouster_ros sensor.launch.xml sensor_hostname:=<ip> viz:=false

# terminal 2 -- odometry (do NOT restart this until REPEAT is done)
ros2 launch localization localization.launch.py

# terminal 3 -- TEACH: start recording. LEAVE THIS RUNNING -- it's a live
# node, not a one-shot command; killing it means there's nothing left to
# receive the save call below.
ros2 launch routing route_recorder.launch.py     # saves to /vehicle_1811/routes by default

# terminal 4 -- drive it: joy_node + teleop_bridge's gamepad_node/serial_bridge_node

# terminal 5 -- once you're back at the start, save WITHOUT stopping terminal 3
# (a ROS2 service call needs the node it's calling to still be alive and
# listening -- this fails/hangs if you ctrl-c terminal 3 first):
ros2 service call /route_recorder_node/save std_srvs/srv/Trigger {}
# now either ctrl-c terminal 3 (it also auto-saves on shutdown, as a fallback),
# or leave it running and keep driving for another ~save later.

# terminal 3 (only once you've ctrl-c'd it above) or any fresh terminal --
# REPEAT: point pure_pursuit at the file terminal 5 just reported saving
ros2 launch control pure_pursuit.launch.py path_file:=/vehicle_1811/routes/route_<timestamp>.csv
ros2 topic echo /cmd/auto     # confirm sane output before ever wiring it to serial_bridge
```

The exact saved filename is printed in the recorder's log line and in the
`~/save` service response (`ros2 service call .../save` echoes it back too).

### What that `ros2 service call` line is actually doing

ROS2 has two ways nodes talk to each other: **topics** (pub/sub — `/odometry`
streams continuously, no reply expected) and **services** (request/response —
a one-shot call, like invoking a function on another process). Recording is
continuous, so it's a topic subscription; "save right now" is a one-time
imperative action, so it's a service — that's why `~/save` exists instead of
just watching a topic.

`ros2 service call <service_name> <service_type> <request>` is the CLI tool
that makes one of these calls by hand:
- `/route_recorder_node/save` — the service name. In the node's own code it's
  declared as `~/save`; `~` expands to the node's name (`route_recorder_node`)
  since it isn't namespaced, giving the full name shown above.
- `std_srvs/srv/Trigger` — the service type: a generic built-in with an empty
  request and a `{success: bool, message: string}` response.
- `{}` — the request contents. `Trigger` has no fields, so it's empty.

Running it sends that request to `route_recorder_node`, which runs its
`~/save` handler (writes the buffer to disk, builds a response), and prints
the response straight back to your terminal — so you see immediately whether
it worked, how many points/meters got saved, and the exact path, without a
second terminal tailing logs.

## Downsampling

Distance-based only: a pose is kept if it's the first one, or at least
`min_spacing_m` (default `0.15`, per the guide's "~0.1-0.2 m of travel")
from the last *kept* point. A stopped vehicle naturally stops adding
points — there's no separate "skip duplicates" step because a near-zero
travel distance already fails the spacing check.

## Build + test

```bash
colcon build --packages-select routing
colcon test --packages-select routing --event-handlers console_direct+
```

`test/test_route_recorder_core.py` unit-tests the downsampling logic
directly (no ROS), and includes one important cross-package check: it
writes a buffer through `format_csv` and loads it back with
`control.pure_pursuit_core.load_csv_path`, to verify the two packages
*actually* agree on the file format rather than just by comment/convention.
That test needs `control` built too:
```bash
colcon build --packages-select routing control
```

## Params

| Param | Default | |
|---|---|---|
| `odom_topic` | `/odometry` | |
| `min_spacing_m` | `0.15` | m between kept waypoints |
| `output_dir` | `/vehicle_1811/routes` | ignored if `output_file` is set; `''` → `<cwd>/routes` instead; gitignored |
| `output_file` | `''` → auto-generated `route_<timestamp>.csv` | |
| `record_on_start` | `true` | false if you'd rather gate via `~start_recording` |
| `odom_timeout` | `1.0` s | informational-only staleness warning while recording |

## Safety

None of this drives anything — it's a passive subscriber and a file
writer, so there's no actuation risk. The one operational risk is silent:
if `/odometry` drops out mid-drive (lidar hiccup), the recorder doesn't
stop or error, it just resumes appending once odometry comes back, leaving
a straight-line gap in the route where the dropout was. It logs a warning
(`odom_timeout`) when this happens, but doesn't fix it — a route with a
suspicious dead-straight segment is worth re-recording.
