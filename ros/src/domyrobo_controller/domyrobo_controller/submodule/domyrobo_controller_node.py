import serial
from rclpy.node import Node
from domyrobo_lib.msg import DiffDriveVelocity



class DomyroboControllerNode(Node):

    
    def __init__(self, name:str, config:dict) -> None:
        # Initiate ROS node
        super().__init__(name + '_controller_node')

        # Create ROS subscriber and timer instances
        self.vel_pub = self.create_subscription(
            DiffDriveVelocity,
            name + '/velocity',
            self.velocityCallback,
            10
        )
        self.write_timer = self.create_timer(
            config["write_time"],
            self.timerCallback
        )

        # Holder variables
        self.linear_vel     = 0.0       # linear velocity in m/s
        self.angular_vel    = 0.0       # angular velocity in rad/s
        self.is_write       = False     # write timer

        # Start serial connection
        self.serial = serial.Serial(config["port"], config["baudrate"])


    def writeVelocity(self) -> None:
        if self.is_write:
            # Write received linear and angular velocities
            msg_str     = str(self.linear_vel) + ',' + str(self.angular_vel) + '\n'
            self.serial.write(msg_str.encode('ascii'))

            # Reset
            self.is_write = False


    def velocityCallback(self, msg):
        self.linear_vel     = msg.linear_vel
        self.angular_vel    = msg.angular_vel

    
    def timerCallback(self):
        self.is_write = True