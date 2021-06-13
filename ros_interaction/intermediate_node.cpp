#include <ros/ros.h>
#include <vision_msgs/Detection2DArray.h>
#include <std_msgs/String.h>

class TestRos{
  ros::NodeHandle nh;
  ros::Subscriber sub;
  ros::Publisher pub;

  std_msgs::String output_msg;
  float x_co;
  float y_co;
  float l_xlimit = 630;
  float u_xlimit = 830;

  void callback_receive_detection(const vision_msgs::Detection2DArrayConstPtr det_msg){
    ROS_INFO("%f", det_msg->detections[0].bbox.center.x);
    x_co = det_msg->detections[0].bbox.center.x;
    y_co = det_msg->detections[0].bbox.center.y;

    if((x_co > l_xlimit) && (x_co < u_xlimit)){
      output_msg.data = "Keep going";
    }else{
      output_msg.data = "Stop!";
    }

    pub.publish(output_msg);
  }

public:
  TestRos(){
    sub = nh.subscribe("detectnet/detections", 1000, &TestRos::callback_receive_detection, this);
    pub = nh.advertise<std_msgs::String>("/movement_status", 10);
  }
  ~TestRos(){}
};

int main(int argc, char **argv){
  ros::init(argc, argv, "intermediate");
  TestRos test_ros;
  ros::spin();
  ros::shutdown();
  return 0;
}
