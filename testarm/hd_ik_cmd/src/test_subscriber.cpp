#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
//MOVE IT
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>


void chatterCallback(const sensor_msgs::JointState::ConstPtr& msg)
{

ROS_INFO("joint_states_received %.9f",msg->position[0]);
}


int main(int argc, char **argv)
{
ros::init(argc,argv,"test_subscribe");
ros::NodeHandle nh;
ROS_INFO("begin_test");


// define user callback queue
  ros::CallbackQueue string_queue;
  // create options for subscriber and pass pointer to our custom queue
  ros::SubscribeOptions ops =
    ros::SubscribeOptions::create<sensor_msgs::JointState>(
      "/joint_states", // topic name
      1000, // queue length
      chatterCallback, // callback
      ros::VoidPtr(), // tracked object, we don't need one thus NULL
      &string_queue // pointer to callback queue object
    );
  // subscribe
  ros::Subscriber sub1 = nh.subscribe(ops);


ros::AsyncSpinner spinner(1, &string_queue);
spinner.start();



ros::Rate r(10); // 10 hz
while (ros::ok())
  {
    ros::spinOnce();

    r.sleep();
  }

return 0;

}
