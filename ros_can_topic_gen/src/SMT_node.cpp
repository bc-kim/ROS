#include "ros/ros.h"
#include "ros_can_topic_gen/Node_msgs.h"
#include "iostream"

int main(int argc,char **argv)
{
ros::init(argc,argv,"SMT_node");
ros::NodeHandle nh;

ros::Publisher ros_tutorial_pub = nh.advertise<ros_can_topic_gen::Node_msgs>("node_messages",5);
ros::Rate loop_rate(10);

ros_can_topic_gen::Node_msgs msg;

int count = 0;
int nodenum = 0;
char key;
int key2;

std::cout<<"Enter Nodenumber:  ";
std::cin>>nodenum;

while(ros::ok())
{
std::cout<<" "<<std::endl;
std::cout<<"---------------------SMT controller---------------------- "<<std::endl;
std::cout<<"Check_current_status:C, Begin operation: O"<<std::endl;
std::cout<<"Position mode: P, Velocity mode: V, Torque mode: T"<<std::endl;
std::cout<<"Send target value: S, Quit: Q"<<std::endl;
std::cout<<"--------------------------------------------------------- "<<std::endl;
std::cout<<" "<<std::endl;
std::cin>>key;

if (key == 'c' || key == 'C')
    {
        msg.node_messages = 5;
        msg.sub_index = 1;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }

else if (key == 'O'|| key == 'o')
    {
        msg.node_messages = 5;
        msg.sub_index = 2;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }
else if (key == 'P'|| key == 'p')
    {       
        msg.node_messages = 5;
        msg.sub_index = 3;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }

else if (key == 'V'|| key == 'v')
    {
        msg.node_messages = 5;
        msg.sub_index = 4;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);        
    }
else if (key == 'T'|| key == 't')
{
    msg.node_messages = 5;
    msg.sub_index = 5;
    msg.node_num = nodenum;
    ros_tutorial_pub.publish(msg);        
}
else if (key == 'S'|| key == 's')
    {
        msg.node_messages = 5;
        msg.sub_index = 6;
        msg.node_num = nodenum;
        std::cout<<" "<<std::endl;
        std::cout<<"---------------------SMT controller---------------------- "<<std::endl;
        std::cout<<"Type target value (type in hexademical) "<<std::endl;
        std::cout<<"(If, 0x00|0x02|0x03|0x00 -> type 00020300) "<<std::endl;
        std::cout<<"--------------------------------------------------------- "<<std::endl;
        std::cout<<" "<<std::endl;
        std::cin>>key2;
        //와야하는 정보: 0xaa 0xbb 0xcc 0xdd//
        /*std::cout<<16*(((key2/10000)/100)/10)+((key2/10000)/100)%10<<std::endl; // aa
        std::cout<<16*(((key2/10000)%100)/10)+((key2/10000)%100)%10<<std::endl; // bb
        std::cout<<16*(((key2%10000)/100)/10)+((key2%10000)/100)%10<<std::endl; // cc
        std::cout<<16*(((key2%10000)%100)/10)+((key2%10000)%100)%10<<std::endl; // dd*/
        msg.can_msg1 = 16*(((key2%10000)/100)/10)+((key2%10000)/100)%10;
        msg.can_msg2 = 16*(((key2%10000)%100)/10)+((key2%10000)%100)%10;
        msg.can_msg3 = 16*(((key2/10000)/100)/10)+((key2/10000)/100)%10;
        msg.can_msg4 = 16*(((key2/10000)%100)/10)+((key2/10000)%100)%10;
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

