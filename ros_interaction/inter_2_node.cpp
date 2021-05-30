#include <ros/ros.h>
#include <vision_msgs/Detection2DArray.h>
#include <std_msgs/String.h>

//global variables
float x_co;
float y_co:

void callback_receive_detect(const vision_msgs::Detection2DArrayConstPtr det_msg){
  x_co = det_msg->detections[0].bbox.center.x;
  y_co = det_msg->detections[0].bbox.center.y;
  ROS_INFO("%f", det_msg->detections[0].bbox.center.x);

}

int main(int argc, char **argv){
  ros::init(argc, argv, "inter_2");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("detectnet/detections", 1000, callback_receive_detect);

  ros::spin();

}
