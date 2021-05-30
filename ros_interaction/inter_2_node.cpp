#include <ros/ros.h>
#include <vision_msgs/Detection2DArray.h>
#include <std_msgs/String.h>

//global variables
float x_co;
float y_co:
bool isdetect;

float u_xlimit;
float l_xlimit;
float u_ylimit;
float l_ylimit;

void callback_receive_detect(const vision_msgs::Detection2DArrayConstPtr det_msg){
  if(det_msg->detections[0]){
    isdetect = true;
  }
  ROS_INFO(isdetect ? "true" : "false");
  x_co = det_msg->detections[0].bbox.center.x;
  y_co = det_msg->detections[0].bbox.center.y;
  ROS_INFO("%f", det_msg->detections[0].bbox.center.x);

}

int main(int argc, char **argv){
  ros::init(argc, argv, "inter_2");
  ros::NodeHandle nh;
  
  //subscriber to monitor x and y coordinates of detection
  ros::Subscriber sub = nh.subscribe("detectnet/detections", 1000, callback_receive_detect);
  
  //publisher to publish stop command to robotic arm node
  ros::Publisher pub = nh.advertise<std_msgs::String>("/robot_status", 10);
  
  while(ros::ok()){
    if((x_co > l_xlimit) && (x_co < u_xlimit)){
      std_msgs::String msg;
      msg.data = "Stop Wrist Rotate";
      pub.publish(msg);
    }
    
  }

  ros::spin();

}
