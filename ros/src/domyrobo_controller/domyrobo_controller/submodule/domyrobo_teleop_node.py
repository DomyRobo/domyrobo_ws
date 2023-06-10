from rclpy.node import Node
from domyrobo_lib.msg import DiffDriveVelocity
import getch


class DomyroboTeleopNode(Node):


    def __init__(self, name:str, config:dict) -> None:
        # Initiate ROS node
        super().__init__(name + '_teleop_control_node')

        # Create ROS publisher
        self.vel_pub = self.create_publisher(
            DiffDriveVelocity,
            name + '/velocity',
            10
        )

        # Value to publish
        self.MOVE_FORWARD   = (config["move_forward"]["linear_vel"],config["move_forward"]["angular_vel"])
        self.MOVE_BACKWARD  = (config["move_backward"]["linear_vel"], config["move_backward"]["angular_vel"])
        self.TURN_RIGHT     = (config["turn_right"]["linear_vel"], config["turn_right"]["angular_vel"])
        self.TURN_LEFT      = (config["turn_left"]["linear_vel"], config["turn_left"]["angular_vel"])

        self.get_logger().info("====[ Domyrobo Teleoperate Control ]====")


    def teleopControl(self) -> None:
        # Create msg
        msg     = DiffDriveVelocity()
        
        # Read keyboard input
        char    = getch.getch()

        if char == 'w' or char == 'W':
            msg.linear_vel  = self.MOVE_FORWARD[0]
            msg.angular_vel = self.MOVE_FORWARD[1]
            self.get_logger().info(f">> Key pressed: {char}")
            self.get_logger().info(">> Move forward!")

        elif char == 'd' or char == 'D':
            msg.linear_vel  = self.TURN_RIGHT[0]
            msg.angular_vel = self.TURN_RIGHT[1]
            self.get_logger().info(f">> Key pressed: {char}")
            self.get_logger().info(">> Turn right!")

        elif char == 's' or char == 'S':
            msg.linear_vel  = self.MOVE_BACKWARD[0]
            msg.angular_vel = self.MOVE_BACKWARD[1]
            self.get_logger().info(f">> Key pressed: {char}")
            self.get_logger().info(">> Move backward!")

        elif char == 'a' or char == 'A':
            msg.linear_vel  = self.TURN_LEFT[0]
            msg.angular_vel = self.TURN_LEFT[1]
            self.get_logger().info(f">> Key pressed: {char}")
            self.get_logger().info(">> Turn left!")

        elif char == 'q' or char == 'Q':
            msg.linear_vel  = 0.0
            msg.angular_vel = 0.0
            self.get_logger().info(f">> Key pressed: {char}")
            self.get_logger().info(">> Stop!")

        # Publish value
        self.vel_pub.publish(msg)