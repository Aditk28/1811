import json
import threading

import rclpy
import serial
from rclpy.node import Node
from vehicle_msgs.msg import VehicleCommand, VehicleState

MAX_SPEED_MPH = 12.5  # lowered for bench/first-drive testing; raise once trusted


class SerialBridgeNode(Node):
    def __init__(self):
        super().__init__('serial_bridge_node')
        self.declare_parameter('port', '/dev/ttyACM0')
        self.declare_parameter('baud', 57600)
        port = self.get_parameter('port').value
        baud = self.get_parameter('baud').value

        self.ser = serial.Serial(port, baud, timeout=0.1)

        self.sub = self.create_subscription(VehicleCommand, '/vehicle_command', self.on_command, 10)
        self.state_pub = self.create_publisher(VehicleState, '/vehicle_state', 10)

        self._stop = False
        self._read_thread = threading.Thread(target=self._read_loop, daemon=True)
        self._read_thread.start()

    def on_command(self, msg: VehicleCommand):
        # throttle is normalized -1..1; firmware wants an actual target speed in mph.
        speed_mph = msg.throttle * MAX_SPEED_MPH
        payload = {
            "speed": round(speed_mph, 3),
            "steering": round(msg.steer, 3),
            "braking": round(msg.brake, 3),
        }
        line = json.dumps(payload) + "\n"
        self.ser.write(line.encode('ascii'))

    def _read_loop(self):
        # The firmware may send nothing, a JSON object, or (as observed) bare
        # numbers / debug text. Parse defensively so a stray line never kills
        # this thread and silently stops state read-back.
        while not self._stop and rclpy.ok():
            try:
                line = self.ser.readline().decode('ascii', errors='ignore').strip()
            except serial.SerialException as exc:
                self.get_logger().error(f'Serial read failed: {exc}')
                continue
            if not line:
                continue
            try:
                data = json.loads(line)
            except json.JSONDecodeError:
                self.get_logger().warning(
                    f'Non-JSON serial line, ignoring: {line!r}',
                    throttle_duration_sec=5.0)
                continue
            # json.loads happily returns floats/ints/lists for lines like "2.5".
            # We only handle JSON objects; skip anything else.
            if not isinstance(data, dict):
                self.get_logger().warning(
                    f'Serial line is not a JSON object, ignoring: {line!r}',
                    throttle_duration_sec=5.0)
                continue
            state = VehicleState()
            state.header.stamp = self.get_clock().now().to_msg()
            state.speed_mps = float(data.get('speed', 0.0)) * 0.44704  # mph -> m/s, if firmware echoes speed back
            state.battery_v = float(data.get('battery', 0.0))
            state.watchdog_tripped = bool(data.get('watchdog', 0))
            self.state_pub.publish(state)

    def destroy_node(self):
        self._stop = True
        self.ser.close()
        super().destroy_node()


def main():
    rclpy.init()
    node = SerialBridgeNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()