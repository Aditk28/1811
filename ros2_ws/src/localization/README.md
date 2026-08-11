# localization

Live lidar odometry for the 1811 vehicle: a thin launch/config wrapper around
**PRBonn upstream KISS-ICP**. Consumes `/ouster/points`, produces `/odometry`
and the `odom → base_link` TF. This is **step B1** of the teach-and-repeat
milestone — see [`docs/teach_and_repeat_guide.md`](../../../docs/teach_and_repeat_guide.md).

Upstream KISS-ICP (not Nova's fork) is deliberate: you want live **odometry**,
not relocalization against a saved map. See
[`docs/teach_and_repeat_plan.md`](../../../docs/teach_and_repeat_plan.md).

## 1. Vendor KISS-ICP (once)

Add PRBonn kiss-icp as a submodule, matching how `ouster-ros` is vendored:

```bash
cd ~/1811          # repo root (host)
git submodule add https://github.com/PRBonn/kiss-icp.git ros2_ws/src/kiss-icp
git submodule update --init --recursive
```

Pin it to a release later (`git -C ros2_ws/src/kiss-icp checkout <tag>`) so the
build is reproducible — bumping is then a one-line reviewable diff.

## 2. Build (on the Karbon, in the container)

```bash
docker compose run --rm dev bash
cd /vehicle_1811/ros2_ws
colcon build --packages-select kiss_icp localization
source install/setup.bash
```

**Build gotchas:**
- KISS-ICP's ROS wrapper pulls a few C++ deps (Sophus, tsl-robin-map, …) via
  CMake `FetchContent` at build time — the container needs **network access on
  the first build**. Eigen is already in the image.
- The colcon package is named **`kiss_icp`** (underscore), not `kiss-icp`.

## 3. Run + verify (the B1 done-when)

Start the Ouster driver, then this:

```bash
# terminal 1 — lidar
ros2 launch ouster_ros sensor.launch.xml sensor_hostname:=<ip> viz:=false   # + udp_profile_lidar:=LEGACY if on fw 3.0.1

# terminal 2 — odometry
ros2 launch localization localization.launch.py
```

Confirm the outputs:

```bash
ros2 topic hz /odometry            # should tick at ~scan rate (10-20 Hz)
ros2 topic echo /odometry --once   # pose should change as you drive
ros2 run tf2_tools view_frames     # odom -> base_link present, once
```

**Done when:** in RViz (fixed frame `odom`), driving under teleop keeps the
accumulated point cloud **crisp** — walls stay thin lines, not smeared — and
`base_link` tracks correctly through the map. Smearing/doubling = bad extrinsics
(recheck the URDF lidar placement) or bad config.

## Version drift — the thing that will trip you up

KISS-ICP's launch **argument names** and its **output odometry topic** change
between releases. This wrapper assumes the common layout (`topic`, `base_frame`,
`odom_frame`, `publish_odom_tf`, `visualize`, and output on `/kiss/odometry`).
Verify against your checkout and adjust
[`launch/localization.launch.py`](launch/localization.launch.py):

```bash
ros2 launch kiss_icp odometry.launch.py -s     # real argument names
ros2 topic list | grep -i odom                 # real odom topic (fix the SetRemap 'src')
```

## Contract

| | |
|---|---|
| **Subscribes** | `/ouster/points` (`sensor_msgs/PointCloud2`) |
| **Publishes** | `/odometry` (`nav_msgs/Odometry`), TF `odom → base_link` |
| **Owns** | the `odom` frame — nothing else may publish it |
| **Depends on** | URDF TF `base_link → os_sensor → os_lidar` (vehicle_1811_description) |
