#cmake_minimum_required(VERSION 3.0.2)
#project(hd_mp)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
#find_package(catkin REQUIRED COMPONENTS
#  roscpp
#  rospy
#  std_msgs
#)
cmake_minimum_required(VERSION 2.8.3)
project(hd_ik_demo)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    moveit_ros_planning
    moveit_ros_planning_interface
    moveit_core
    geometry_msgs
    rviz_visual_tools
    moveit_visual_tools
    
)

catkin_package(
   LIBRARIES
   INCLUDE_DIRS
   CATKIN_DEPENDS
    roscpp
    moveit_ros_planning
    moveit_ros_planning_interface
    geometry_msgs
    moveit_core
    moveit_visual_tools
    interactive_markers
    tf2_geometry_msgs
  DEPENDS
    EIGEN3
)



include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(move_group_hd src/move_group_hd.cpp)
add_dependencies(move_group_hd ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_group_hd ${catkin_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS move_group_hd DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
#install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

