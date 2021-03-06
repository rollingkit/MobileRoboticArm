//Prior to compiling anr running this node, need to make a ros package with the library from the LidarLite v3 for
//Raspberry Pi given here: https://github.com/garmin/LIDARLite_RaspberryPi_Library
//After that the CMakeLists.txt of your package needs to be updated to include the relevant header files from the library. 

//Author: Sivankit Bhanot


#include <ros/ros.h>
#include <linux/types.h>
#include <cstdio>

#include <lidar_library/lidarlite_v3.h>
#include <std_msgs/UInt16.h>

LIDARLite_v3 myLidarLite;

int main(int argc, char **argv)
{
  __u16 distance;
  __u8 busyFlag;

  ros::init(argc, argv, "lidar_mod");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<std_msgs::UInt16>("lidar_values", 10);

  ros::Rate rate(3);

  while(ros::ok()){
    myLidarLite.i2c_init();
    myLidarLite.configure(0);

    while(1){
      busyFlag = myLidarLite.getBusyFlag();
      if (busyFlag == 0x00){
        myLidarLite.takeRange();
        distance = myLidarLite.readDistance();
        //printf("%4d\n", distance);
        std_msgs::UInt16 msg;
        msg.data = distance;
        pub.publish(msg);
        rate.sleep();
      }
    }
  }
}
