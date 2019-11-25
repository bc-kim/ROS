#include "ros/ros.h"
#include "ros_can_topic_gen/Node_msgs.h"
#include "iostream"

int main(int argc,char **argv)
{
ros::init(argc,argv,"NMT_node");
ros::NodeHandle nh;

ros::Publisher ros_tutorial_pub = nh.advertise<ros_can_topic_gen::Node_msgs>("node_messages",5);
ros::Rate loop_rate(10);

ros_can_topic_gen::Node_msgs msg;

int count = 0;
int nodenum = 0;
char key;

std::cout<<"Enter Nodenumber:  ";
std::cin>>nodenum;

while(ros::ok())
{
std::cout<<" "<<std::endl;
std::cout<<"---------------------NMT controller---------------------- "<<std::endl;
std::cout<<"NMT_check:C, NMT_Pre_operation: P, NMT_Operation_Stop: S"<<std::endl;
std::cout<<"NMT_Reset:R, NMT_operational:   O, NMT_Reset_commun:   E"<<std::endl;
std::cout<<"quit: Q"<<std::endl;
std::cout<<"--------------------------------------------------------- "<<std::endl;
std::cout<<" "<<std::endl;
std::cin>>key;

if (key == 'O' || key == 'o')
    {
        msg.node_messages = 2;
        msg.sub_index = 1;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }

else if (key == 'C'|| key == 'c')
    {
        msg.node_messages = 1;
        msg.sub_index = 0;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }
else if (key == 'P'|| key == 'p')
    {       
        msg.node_messages = 2;
        msg.sub_index = 2;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }

else if (key == 'S'|| key == 's')
    {
        msg.node_messages = 2;
        msg.sub_index = 3;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);        
    }
else if (key == 'R'|| key == 'r')
    {
        msg.node_messages = 2;
        msg.sub_index = 4;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);        
    }
else if (key == 'E'|| key == 'e')
    {
        msg.node_messages = 2;
        msg.sub_index = 5;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);        
    }

else if(key == 'Q'||key == 'q')
    {
        return 0;
    }   

loop_rate.sleep();

++count;
}
return 0;
}
