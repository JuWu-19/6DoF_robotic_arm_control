
cmake_minimum_required(VERSION 2.8.3)
project(hd_ik_cmd)

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

add_executable(test_subscriber src/test_subscriber.cpp)
add_dependencies(test_subscriber ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(test_subscriber ${catkin_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS test_subscriber DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(move_group_cmd src/move_group_cmd.cpp)
add_dependencies(move_group_cmd ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_group_cmd ${catkin_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS move_group_cmd DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
#install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

