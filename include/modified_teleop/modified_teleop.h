#ifndef OPEN_MANIPULATOR_TELEOP_H
#define OPEN_MANIPULATOR_TELEOP_H

#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

#include <termios.h>
#include "open_manipulator_msgs/SetJointPosition.h"
#include "open_manipulator_msgs/SetKinematicsPose.h"

#include <geometry_msgs/PoseStamped.h>

#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

#define NUM_OF_JOINT 4
#define DELTA 0.01
#define JOINT_DELTA 0.05
#define PATH_TIME 1.5

class OpenManipulatorTeleop
{
 private:
  // ROS NodeHandle
  ros::NodeHandle node_handle_;
  ros::NodeHandle priv_node_handle_;

  ros::ServiceClient goal_joint_space_path_from_present_client_;
  ros::ServiceClient goal_task_space_path_from_present_position_only_client_;
  ros::ServiceClient goal_joint_space_path_client_;
  ros::ServiceClient goal_tool_control_client_;
  ros::ServiceClient goal_task_space_path_position_only_client_;
  //position + orientation
  ros::ServiceClient goal_task_space_path_client_;


  ros::Subscriber joint_states_sub_;
  ros::Subscriber kinematics_pose_sub_;
  ros::Subscriber input_kinematics_pose_sub_;//kk

  std::vector<double> present_joint_angle_;
  std::vector<double> present_kinematic_position_;
  std::vector<double> input_kinematic_position_;//goal position(input)
  std::vector<double> input_kinematic_orientation_;//goal orientation (input)
  open_manipulator_msgs::KinematicsPose kinematics_pose_;


  struct termios oldt_;

 public:

  OpenManipulatorTeleop();
  ~OpenManipulatorTeleop();

  void initClient();
  void initSubscriber();

  void jointStatesCallback(const sensor_msgs::JointState::ConstPtr &msg);
  void kinematicsPoseCallback(const open_manipulator_msgs::KinematicsPose::ConstPtr &msg);

  void kinematicsPoseinput(const geometry_msgs::Pose::ConstPtr &msg);

  std::vector<double> getPresentJointAngle();
  std::vector<double> getPresentKinematicsPose();
  std::vector<double> getInputKinematicsPose();//input


  bool setJointSpacePathFromPresent(std::vector<std::string> joint_name, std::vector<double> joint_angle, double path_time);
  bool setJointSpacePath(std::vector<std::string> joint_name, std::vector<double> joint_angle, double path_time);
  bool setTaskSpacePathFromPresentPositionOnly(std::vector<double> kinematics_pose, double path_time);
  bool setTaskSpacePathPositionOnly(std::vector<double> kinematics_pose, double path_time);
  //added
  bool setTaskSpacePath(std::vector<double> kinematics_pose, std::vector<double> kinematics_orientation, double path_time);


  bool setToolControl(std::vector<double> joint_angle);

  void printText();
  void setGoal(char ch);

  void restoreTerminalSettings(void);
  void disableWaitingForEnter(void);

};

#endif //OPEN_MANIPULATOR_TELEOP_H
