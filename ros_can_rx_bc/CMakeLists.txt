cmake_minimum_required(VERSION 2.8.3)
project(ros_can_rx_bc)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  can_msgs
)

add_message_files(FILES msg_FP.msg msg_FP2.msg msg_FP3.msg msg_FP4.msg msg_Error.msg msg_to_topic.msg)

generate_messages(
   DEPENDENCIES
   std_msgs
)

catkin_package(
  INCLUDE_DIRS 
    include
  LIBRARIES
    ros_can_rx_bc
    can_trans
  CATKIN_DEPENDS
    roscpp
    std_msgs
    can_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node src/ros_can_rx_bc.cpp)

add_library(can_trans
  src/can_trans.cpp
)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} can_trans)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} can_trans)

## node rx_2
add_executable(ros_can_rx_to_node src/ros_can_to_node.cpp)
add_dependencies(ros_can_rx_to_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} can_trans)
target_link_libraries(ros_can_rx_to_node ${catkin_LIBRARIES} can_trans)
