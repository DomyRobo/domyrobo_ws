from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package     = 'domyrobo_controller',
            executable  = 'domyrobo_controller_main'
        ),
        Node(
            package     = 'domyrobo_controller',
            executable  = 'domyrobo_teleop_main'
        ),
    ])