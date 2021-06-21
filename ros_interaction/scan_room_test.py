from interbotix_sdk.robot_manipulation import InterbotixRobot
from interbotix_descriptions import interbotix_mr_descriptions as mrd
import numpy as np
import rospy
from std_msgs.msg import String

# This script makes the end-effector perform pick, pour, and place tasks
#
# To get started, open a terminal and type 'roslaunch interbotix_sdk arm_run.launch robot_name:=wx250s use_time_based_profile:=true gripper_operating_mode:=pwm'
# Then change to this directory and type 'python scan_room_test.py'

cmd_msg = ""

def callback_rec(msg):
    #rospy.loginfo("Message received: ")
    #rospy.loginfo(msg)
    global cmd_msg
    cmd_msg = msg.data
    #rospy.loginfo(cmd_msg)

def main():
    arm = InterbotixRobot(robot_name="rx150", mrd=mrd)
    sub = rospy.Subscriber("/robot_status", String, callback_rec)

    arm.set_ee_pose_components(x=0.2, z=0.3)
    arm.set_single_joint_position("waist", np.pi/2.0)
    angle_dec = np.pi/36.0 # 5 degree increments
    #angle_dec = np.pi/18.0 # 10 degree increments
    count = 1
    while np.pi/2.0 - (count*angle_dec) > 0:
	#print(cmd_msg)
	global cmd_msg
	rospy.loginfo(cmd_msg)
	if cmd_msg == "Stop!":
		break
	else:
		arm.set_single_joint_position("waist", np.pi/2.0 - (count*angle_dec))
		count +=1
		

    arm.set_single_joint_position("waist", 0)
    #arm.open_gripper()
    #arm.set_ee_cartesian_trajectory(x=0.1, z=-0.16)
    #arm.close_gripper()
    #arm.set_ee_cartesian_trajectory(x=-0.1, z=0.16)
    #arm.set_single_joint_position("waist", -np.pi/2.0)
    #arm.set_ee_cartesian_trajectory(pitch=1.5)
    #arm.set_ee_cartesian_trajectory(pitch=-1.5)
    #arm.set_single_joint_position("waist", np.pi/2.0)
    #arm.set_ee_cartesian_trajectory(x=0.1, z=-0.16)
    #arm.open_gripper()
    #arm.set_ee_cartesian_trajectory(x=-0.1, z=0.16)
    #arm.go_to_home_pose()
    arm.go_to_sleep_pose()

if __name__=='__main__':
    main()
