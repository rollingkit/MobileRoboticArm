from interbotix_sdk.robot_manipulation import InterbotixRobot
from interbotix_descriptions import interbotix_mr_descriptions as mrd

#jp = [[0.030679617077112198, -0.03221359848976135, 1.607611894607544, -0.1288543939590454,       -0.012271846644580364],
 #     [0.9035146832466125, 0.1257864236831665, -1.0170292854309082, 1.0737866163253784, 0.07363107800483704],
  #    [-2.5095925331115723, 0.0076699042692780495, -0.45712628960609436, 0.4939418137073517, -0.11811652034521103]]

jp = [[0.14, -0.21, -0.03, -0.35, -0.44],
      [0.14, -1.38, -0.03, -0.35, -0.44],
      [0.14, -0.01, -0.01, 1.75, -0.44]]


def main():
	arm = InterbotixRobot(robot_name="rx150", mrd=mrd)
	arm.go_to_home_pose()

	arm.set_joint_positions(jp[0])
	arm.set_joint_positions(jp[1])
	arm.set_gripper_pressure(1.0)
	arm.open_gripper()
	arm.set_joint_positions(jp[2])
	arm.go_to_home_pose()
	arm.close_gripper()
	arm.go_to_sleep_pose()
	

if __name__=="__main__":
	main()
