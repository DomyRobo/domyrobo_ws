#!/usr/bin/env python3
import rclpy
import yaml
from .submodule.domyrobo_teleop_node import DomyroboTeleopNode


# Main process
def main():
    DOMYROBO_LIB_PACKAGE_PATH           = '/home/domyrobo/Workspaces/domyrobo_ws/ros/src/domyrobo_lib'
    DOMYROBO_CONTROLLER_PACKAGE_PATH    = '/home/domyrobo/Workspaces/domyrobo_ws/ros/src/domyrobo_controller'


    # Parse robot unique information from domyrobo_lib
    # Parse serial communication parameter from domyrobo_controller
    with open(DOMYROBO_LIB_PACKAGE_PATH + '/config/information_config.yaml', 'r') as yaml_file:
        info_config = yaml.safe_load(yaml_file)
    with open(DOMYROBO_CONTROLLER_PACKAGE_PATH + '/config/teleop_speed_config.yaml', 'r') as yaml_file:
        teleop_config = yaml.safe_load(yaml_file)


    # Define robot name
    ROBOT_NAME = info_config["name"] + info_config["uid"]


    # Create node
    rclpy.init()
    teleop_control_node = DomyroboTeleopNode(ROBOT_NAME, teleop_config)


    # Loop
    while rclpy.ok():
        teleop_control_node.teleopControl()


    # Destroy
    teleop_control_node.destroy_node()
    rclpy.shutdown()