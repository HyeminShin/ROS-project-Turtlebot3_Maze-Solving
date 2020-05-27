#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  
  MoveBaseClient ac("move_base", true);


  while(!ac.waitForServer(ros::Duration(3.0))){
    ROS_INFO("Waiting for the move_base action p");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = 2.0;
  goal.target_pose.pose.orientation.w = 2.0;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Moved 2 meter forward");
  else
    ROS_INFO("Failed to move forward 2 meter because of uncertain error");

  return 0;
}
