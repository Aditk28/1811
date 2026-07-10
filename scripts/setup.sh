mkdir -p ~/1811/scripts
cat > ~/1811/scripts/setup_karbon.sh << 'EOF'
#!/usr/bin/env bash
# Run on the Karbon OBC after cloning the repo.
# Installs system deps for teleop_bridge, lidar_perception, sensor_fusion.
set -euo pipefail

if [ -z "${ROS_DISTRO:-}" ]; then
  echo "ROS 2 not sourced/installed. Install ROS 2 Humble first, then re-run this script."
  exit 1
fi

echo "Detected ROS_DISTRO=$ROS_DISTRO"

sudo apt update
sudo apt install -y \
  ros-humble-joy \
  ros-humble-pcl-ros \
  ros-humble-pcl-conversions \
  python3-serial \
  python3-colcon-common-extensions

echo "Building..."
cd "$(dirname "$0")/../ros2_ws"
colcon build --packages-select vehicle_msgs teleop_bridge lidar_perception sensor_fusion obc_bringup

echo "Done. Source it with:"
echo "  source ~/1811/ros2_ws/install/setup.bash"
EOF
chmod +x ~/1811/scripts/setup_karbon.sh