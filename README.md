# MobileRoboticArm
Includes code and scripts for working with the Interbotix Reactor X 150 Robotic Arm, Camera and Lidar modules, all operating on the Nvidia Jetson Nano. 


In ros_interaction:
inter_1 contains the 'inter' node which simply subscribes to the /detections topic of detectnet node from Dusty's code. 
intermediate_node.cpp contains the 'intermediate' node which has the similar subscriber to the /detections topic, and also a publisher that publishes to the /movement_status topic. 


Apparatus:

1. Trossen Robotics Reactor X 150 Arm
2. Jetson Nano Mini Computer
3. Raspberry Pi Camera Module V2
4. Garmin Lidar Lite V3


Usage:

After connecting the camera module to the CSI port on the Nano Board, and the Lidar module to the GPIO pins according to the configuration shown here: https://github.com/garmin/LIDARLite_RaspberryPi_Library

The pin configuration for connecting the LIDAR sensor is identical to the one used when connecting it to Raspberry Pi. 
The library for the Raspberry Pi can also be used and executed in the Jetson Nano. 

Once the three components (the arm, the camera, and the Lidar) are set up, we can go about running ROS Nodes. 

For running the intermediate node, we first run the camera and the object detection script which are represented by the detectnet node. To run the object detection in real time on the camera feed, run the detectnet node by following along the commands provided here: https://github.com/dusty-nv/ros_deep_learning

Once this is running, use rosrun intermediate to run the intermediate node.
Use rostopic echo movement_status to see how the detected object's place in the video view window affects the message of either 'Stop' or 'Keep Going'. 

To run the LIDAR node, need to create a catkin package with the C++ libraries provided at https://github.com/garmin/LIDARLite_RaspberryPi_Library.
Then the node can also be run using the rosrun command. 

