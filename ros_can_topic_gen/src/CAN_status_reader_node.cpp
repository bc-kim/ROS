#include "ros/ros.h"
#include "ros_can_topic_gen/MsgTutorial.h"
#include "ros_can_topic_gen/msg_to_topic.h"

void msgCallback(const ros_can_topic_gen::msg_to_topic::ConstPtr& msg)
{
    int i = msg->msg_to_nodes;
    int j = msg->sub_index;
    int n = msg->node_num;
    if(i==2 && j==1)
    {
        ROS_INFO("node %d is operational",n);
    }
    else if(i==2 && j==2)
    {
        ROS_INFO("node %d is stopped", n);
    }

    else if(i==2 && j==3)
    {  
        ROS_INFO("node %d is pre-opearational", n);
    }
}

int main(int argc, char **argv)
{
ros::init(argc,argv,"CAN_Status_reader_node");
ros::NodeHandle nh;
ros::Subscriber ros_tutorial_sub = nh.subscribe("msg_to_topic",1,msgCallback);
ros::spin();

return 0;
}
