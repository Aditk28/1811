mkdir -p ~/1811/scripts
cat > ~/1811/scripts/setup_karbon.sh << 'EOF'
#!/usr/bin/env bash
# Run on the Karbon OBC (or a laptop standing in for it) after cloning the repo.
# Installs system deps for teleop_bridge, lidar_perception, sensor_fusion,
# and builds those packages.
set -euo pipefail

if [ -z "${ROS_DISTRO:-}" ]; then
  echo "ROS 2 not sourced/installed. Install ROS 2 Humble first, then re-run this script."
  echo "See docs/ros2_install.md"
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

pip3 install --user pygame

# The Arduino shows up as /dev/ttyACM0 (or similar) owned by the 'dialout'
# group. Without this, serial_bridge_node fails with "Permission denied".
if ! groups "$USER" | grep -q '\bdialout\b'; then
  echo "Adding $USER to the 'dialout' group (needed for serial port