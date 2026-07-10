import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from vehicle_msgs.msg import VehicleCommand

AXIS_THROTTLE = 1
AXIS_STEER = 0
AXIS_BRAKE = 2
DEADZONE = 0.05


class GamepadNode(Node):
    def __init__(self):
        super().__init__('gamepad_node')
        self.sub = self.create_subscription(Joy, '/joy', self.on_joy, 10)
        self.pub = self.create_publisher(VehicleCommand, '/vehicle_command', 10)

    def apply_deadzone(self, value: float) -> float:
        return 0.0 if abs(value) < DEADZONE else value

    def on_joy(self, msg: Joy):
        cmd = VehicleCommand()
        cmd.header.stamp = self.get_clock().now().to_msg()
        cmd.throttle = self.apply_deadzone(msg.axes[AXIS_THROTTLE])
        cmd.steer = self.apply_deadzone(msg.axes[AXIS_STEER])
        cmd.brake = max(0.0, -msg.axes[AXIS_BRAKE])
        self.pub.publish(cmd)


def main():
    rclpy.init()
    node = GamepadNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()