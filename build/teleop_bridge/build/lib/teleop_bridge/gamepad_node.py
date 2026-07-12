import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from vehicle_msgs.msg import VehicleCommand

# --- Axis mapping ---
# These indices/signs are controller-dependent. Verify with:
#   ros2 topic echo /joy
# while moving each control individually, then adjust the values below
# until they match your actual controller.
AXIS_LEFT_STICK_Y = 1     # left stick vertical  -> throttle
AXIS_RIGHT_STICK_X = 3    # right stick horizontal -> steering
AXIS_LEFT_TRIGGER = 2     # left trigger -> brake

INVERT_THROTTLE = False   # flip to True if pushing the stick up drives backward
INVERT_STEER = False      # flip to True if right on the stick steers left

# Most Linux joystick drivers report triggers resting at +1.0 (released)
# and -1.0 (fully pressed). If yours instead rests at 0.0 and rises to 1.0
# when pressed, set this to False.
TRIGGER_RESTS_AT_PLUS_ONE = True

DEADZONE = 0.05


class GamepadNode(Node):
    def __init__(self):
        super().__init__('gamepad_node')
        self.sub = self.create_subscription(Joy, '/joy', self.on_joy, 10)
        self.pub = self.create_publisher(VehicleCommand, '/vehicle_command', 10)

    def apply_deadzone(self, value: float) -> float:
        return 0.0 if abs(value) < DEADZONE else value

    def trigger_to_brake(self, raw: float) -> float:
        """Normalize a trigger axis to 0.0 (released) .. 1.0 (fully pressed)."""
        brake = (1.0 - raw) / 2.0 if TRIGGER_RESTS_AT_PLUS_ONE else raw
        return max(0.0, min(1.0, brake))

    def on_joy(self, msg: Joy):
        cmd = VehicleCommand()
        cmd.header.stamp = self.get_clock().now().to_msg()

        raw_throttle = self.apply_deadzone(msg.axes[AXIS_LEFT_STICK_Y])
        if INVERT_THROTTLE:
            raw_throttle = -raw_throttle

        raw_steer = self.apply_deadzone(msg.axes[AXIS_RIGHT_STICK_X])
        if INVERT_STEER:
            raw_steer = -raw_steer

        brake = self.trigger_to_brake(msg.axes[AXIS_LEFT_TRIGGER])
        braking = brake > DEADZONE

        # Brake overrides throttle -- never send both nonzero at once.
        cmd.throttle = 0.0 if braking else raw_throttle
        cmd.steer = raw_steer
        cmd.brake = brake if braking else 0.0

        self.pub.publish(cmd)


def main():
    rclpy.init()
    node = GamepadNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()