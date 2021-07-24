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
project(hd_mp)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    moveit_ros_planning
    moveit_ros_planning_interface
    moveit_core
    geometry_msgs
    
)

catkin_package(CATKIN_DEPENDS
    roscpp
    moveit_ros_planning
    moveit_ros_planning_interface
    moveit_core
    geometry_msgs
)



include_directories(
  ${catkin_INCLUDE_DIRS}
)


add_executable(ik_demo src/ik_demo.cpp)
add_dependencies(ik_demo ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(ik_demo ${catkin_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS ik_demo DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
#install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

