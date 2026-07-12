from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(package='joy', executable='joy_node', name='joy_node',
             parameters=[{'deadzone': 0.05}]),
        Node(package='teleop_bridge', executable='gamepad_node', name='gamepad_node'),
        Node(package='teleop_bridge', executable='serial_bridge_node', name='serial_bridge_node',
             parameters=[{'port': '/dev/ttyACM0', 'baud': 115200}]),
    ])