#include "ros/ros.h"
#include "ros_can_topic_gen/MsgTutorial.h"
#include "ros_can_topic_gen/msg_FP.h"
#include "ros_can_topic_gen/msg_FP2.h"
#include "ros_can_topic_gen/msg_FP3.h"
#include "ros_can_topic_gen/msg_FP4.h"

void msgCallback(const ros_can_topic_gen::msg_FP::ConstPtr& msg)
{
ROS_INFO("Force_A = %d", msg->Force_T1);
}

void msgCallback2(const ros_can_topic_gen::msg_FP2::ConstPtr& msg)
{
ROS_INFO("Force_B = %d", msg->Force_I);
}
void msgCallback3(const ros_can_topic_gen::msg_FP3::ConstPtr& msg)
{
ROS_INFO("Force_C = %d", msg->Force_C);
}
void msgCallback4(const ros_can_topic_gen::msg_FP4::ConstPtr& msg)
{
ROS_INFO("Force_D = %d", msg->Force_D);
}

int main(int argc, char **argv)
{
ros::init(argc,argv,"topic_subscriber");
ros::NodeHandle nh;
ros::Subscriber ros_tutorial_sub = nh.subscribe("msg_Force_position",1,msgCallback);
ros::Subscriber ros_tutorial_sub2 = nh.subscribe("msg_Force_position2",1,msgCallback2);
ros::Subscriber ros_tutorial_sub3 = nh.subscribe("msg_Force_position3",1,msgCallback3);
ros::Subscriber ros_tutorial_sub4 = nh.subscribe("msg_Force_position4",1,msgCallback4);
ros::spin();

return 0;
}
