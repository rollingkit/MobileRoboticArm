#include <linux/types.h>
#include <cstdio>

#include <include/lidarlite_v3.h>
#include <std_msgs/UInt16.h>

LIDARLite_v3 myLidarLite;

int main(int argc char **argv){

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

      if(busyFlag == 0x00){
        myLidarLite.takeRange();
        distance = myLidarLite.readDistance();
        std_msgs::UInt16 msg;
        msg.data = distance;
        pub.publish(msg);
        rate.sleep();
      }
    }
  }
}
