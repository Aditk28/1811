"""Live lidar odometry via KISS-ICP, wrapped for the 1811 stack.

Runs PRBonn kiss-icp against the Ouster and republishes its output as the
stack's canonical /odometry, with the odom->base_link TF. Uses base_link so the
pose is the VEHICLE's, not the sensor's — that mapping comes from the URDF
(vehicle_1811_description: base_link -> os_sensor -> os_lidar).

    ros2 launch localization localization.launch.py

>>> VERSION DRIFT WARNING <<<
KISS-ICP's launch argument names AND its output odometry topic name change
between releases. Before trusting this file, check YOUR checkout:

    ros2 launch kiss_icp odometry.launch.py -s      # list the real arguments
    ros2 topic list | grep -i odom                  # find the real odom topic

Then, if needed, adjust the launch_arguments below and the SetRemap 'src'.
"""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import SetRemap
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    pointcloud_topic = LaunchConfiguration("pointcloud_topic")

    kiss_icp_launch = PathJoinSubstitution(
        [FindPackageShare("kiss_icp"), "launch", "odometry.launch.py"]
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            "pointcloud_topic",
            default_value="/ouster/points",
            description="Input lidar point cloud topic (from ouster-ros).",
        ),

        # KISS-ICP publishes odometry on /kiss/odometry in most versions.
        # Remap it to the stack's canonical /odometry so everything downstream
        # (routing, control) shares one name. SetRemap applies to the included
        # launch below. If your checkout already publishes /odometry, delete this
        # line; if it uses a different name, fix 'src' to match `ros2 topic list`.
        SetRemap(src="/kiss/odometry", dst="/odometry"),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([kiss_icp_launch]),
            launch_arguments={
                "topic": pointcloud_topic,
                "base_frame": "base_link",     # report the VEHICLE pose (URDF)
                "odom_frame": "odom",
                "publish_odom_tf": "true",     # KISS-ICP owns odom->base_link
                "visualize": "false",          # headless on the Karbon; view via RViz on the Jetson
            }.items(),
        ),
    ])
