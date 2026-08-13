"""Teleop bringup: gamepad -> /vehicle_command -> Arduino serial.

    ros2 launch teleop_bridge teleop_bridge.launch.py
    ros2 launch teleop_bridge teleop_bridge.launch.py port:=/dev/ttyACM1

SERIAL PORT NOTE: /dev/ttyACM* numbers are assigned in plug order and CHANGE
across replugs/reboots -- that's what silently pointed the bridge at a Linux
serial console (the `{speed:: command not found` errors). For a STABLE path that
never shifts, find the Arduino's by-id link and pass/set that instead:

    ls -l /dev/serial/by-id/
    # then, e.g.:
    ros2 launch teleop_bridge teleop_bridge.launch.py \
        port:=/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_XXXXXXXX-if00
"""
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    port = LaunchConfiguration('port')
    baud = LaunchConfiguration('baud')

    return LaunchDescription([
        DeclareLaunchArgument(
            'port',
            default_value='/dev/ttyACM2',
            description='Arduino serial port. Enumeration-order dependent; prefer a '
                        'stable /dev/serial/by-id/... path (see header).',
        ),
        DeclareLaunchArgument(
            'baud',
            default_value='57600',
            description='Serial baud rate; must match the firmware Serial.begin().',
        ),

        Node(
            package='joy', executable='joy_node', name='joy_node',
            parameters=[{'deadzone': 0.05}],
        ),
        Node(
            package='teleop_bridge', executable='gamepad_node', name='gamepad_node',
        ),
        Node(
            package='teleop_bridge', executable='serial_bridge_node',
            name='serial_bridge_node',
            parameters=[{
                'port': port,
                'baud': ParameterValue(baud, value_type=int),
            }],
        ),
    ])