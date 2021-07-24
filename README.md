# 6DoF robotic arm control

## Objectives
Modelling and visualization of the robotic arm in ROS: XML language is used to describe the model of robotic arm
and then the urdf model is imported into rviz for visualization.

Inverse kinematics solver: provided desired pose of the end-effector of the robotic arm, the inverse kinematics solver
function is designed to compute the corresponding path from pose A to B in joint space with specified interval and
space&joints constraints, and both the real and simulated controllers can take the path to drive the gripper of the
robotic arm to reach the desired pose.

Cartesian trajectory generator: given way-points with detailed positions, velocities, accelerations and efforts and
specifications like time constraints and limits of rotational angle against certain axis, the generated
trajectory msgs::JointTrajectory is obtained to guide the robotic arm move in the space with the desired interpolated
path.
![ik_test1](https://user-images.githubusercontent.com/58901415/126875317-2e8cf769-ff5f-40da-bbf3-f41aca2ad699.gif)
