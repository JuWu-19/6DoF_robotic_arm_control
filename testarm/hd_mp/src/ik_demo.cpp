#include <ros/ros.h>

// MoveIt
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>

// Robot state publishing
#include <moveit/robot_state/conversions.h>
#include <moveit_msgs/DisplayRobotState.h>

// Kinematics
#include <moveit_msgs/GetPositionIK.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "rob_arm_kinematics");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  ros::NodeHandle node_handle;

  // Start a service client
  ros::ServiceClient service_client = node_handle.serviceClient<moveit_msgs::GetPositionIK>("compute_ik");
  ros::Publisher robot_state_publisher =
      node_handle.advertise<moveit_msgs::DisplayRobotState>("hd_robot_state", 1);

  while (!service_client.exists())
  {
    ROS_INFO("Waiting for service");
    ros::Duration(1.0).sleep();
  }

  moveit_msgs::GetPositionIK::Request service_request;
  moveit_msgs::GetPositionIK::Response service_response;

  service_request.ik_request.group_name = "HD15";
  service_request.ik_request.pose_stamped.header.frame_id = "Link_G";
  service_request.ik_request.pose_stamped.pose.position.x = 0.75;
  service_request.ik_request.pose_stamped.pose.position.y = 0.188;
  service_request.ik_request.pose_stamped.pose.position.z = 0.0;

  service_request.ik_request.pose_stamped.pose.orientation.x = 0.0;
  service_request.ik_request.pose_stamped.pose.orientation.y = 0.0;
  service_request.ik_request.pose_stamped.pose.orientation.z = 0.0;
  service_request.ik_request.pose_stamped.pose.orientation.w = 1.0;

  /* Call the service */
  service_client.call(service_request, service_response);
  ROS_INFO_STREAM(
      "Result: " << ((service_response.error_code.val == service_response.error_code.SUCCESS) ? "True " : "False ")
                 << service_response.error_code.val);

  /* Filling in a seed state */
  robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
  robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
  robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(kinematic_model));
  const robot_state::JointModelGroup* joint_model_group = kinematic_model->getJointModelGroup("HD15");

  service_request.ik_request.robot_state.joint_state.name = joint_model_group->getJointModelNames();

  /* Get the joint values and put them into the message, this is where you could put in your own set of values as
   * well.*/
  kinematic_state->setToRandomPositions(joint_model_group);
  kinematic_state->copyJointGroupPositions(joint_model_group,
                                           service_request.ik_request.robot_state.joint_state.position);

  /* Call the service again*/
  service_client.call(service_request, service_response);
  ROS_INFO_STREAM(
      "Result: " << ((service_response.error_code.val == service_response.error_code.SUCCESS) ? "True " : "False ")
                 << service_response.error_code.val);

  /* Check for collisions*/
  service_request.ik_request.avoid_collisions = true;

  /* Call the service again*/
  service_client.call(service_request, service_response);

  ROS_INFO_STREAM(
      "Result: " << ((service_response.error_code.val == service_response.error_code.SUCCESS) ? "True " : "False ")
                 << service_response.error_code.val);

  /* Visualize the result*/
  moveit_msgs::DisplayRobotState msg;
  kinematic_state->setVariableValues(service_response.solution.joint_state);
  robot_state::robotStateToRobotStateMsg(*kinematic_state, msg.state);
  robot_state_publisher.publish(msg);

  // Sleep to let the message go through
  ros::Duration(2.0).sleep();

  ros::shutdown();
  return 0;
}
