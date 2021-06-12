# MobileRoboticArm
Includes code and scripts for working with the Interbotix Reactor X 150 Robotic Arm, Camera and Lidar modules, all operating on the Nvidia Jetson Nano. 


In ros_interaction:
inter_1 contains the 'inter' node which simply subscribes to the /detections topic of detectnet node from Dusty's code. 
intermediate_node.cpp contains the 'intermediate' node which has the similar subscriber to the /detections topic, and also a publisher that publishes to the /movement_status topic. 
