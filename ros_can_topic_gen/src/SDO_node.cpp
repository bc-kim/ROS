#include "ros/ros.h"
#include "ros_can_topic_gen/Node_msgs.h"
#include "iostream"

int main(int argc,char **argv)
{
ros::init(argc,argv,"SDO_node");
ros::NodeHandle nh;

ros::Publisher ros_tutorial_pub = nh.advertise<ros_can_topic_gen::Node_msgs>("node_messages",5);
ros::Rate loop_rate(10);

ros_can_topic_gen::Node_msgs msg;

int count = 0;
int nodenum = 0;
char key;
char key2;
int key3;

std::cout<<"Enter Nodenumber:  ";
std::cin>>nodenum;
std::cout<<" "<<std::endl;
std::cout<<"---------------------SDO controller---------------------- "<<std::endl;
std::cout<<"Current Status: C, Enable operation: E"<<std::endl;
std::cout<<"Position mode: P, Velocity mode: V, Torque mode: T"<<std::endl;
std::cout<<"quit: Q"<<std::endl;
std::cout<<"--------------------------------------------------------- "<<std::endl;
std::cout<<" "<<std::endl;
std::cin>>key;
while(ros::ok())
{   
    /* key2 는 actuator에 relative target인지, absolute target인지 확인하는 용도로 사용함.
    // 또한, key2에 q나 Q를 입력하면 다시 밖으로 나올 수 있도록 짰기 때문에 코드 밖으로 나오는 기능도 함.
    */
    if(key2=='Q'||key2=='q')
    {
        std::cout<<" "<<std::endl;
        std::cout<<"---------------------SDO controller---------------------- "<<std::endl;
        std::cout<<"Current Status: C"<<std::endl;
        std::cout<<"Position mode: P, Velocity mode: V, Torque mode: T"<<std::endl;
        std::cout<<"quit: Q"<<std::endl;
        std::cout<<"--------------------------------------------------------- "<<std::endl;
        std::cout<<" "<<std::endl;
        std::cin>>key;
    }

    /* 아직 SDO를 이용한 driver 상황 확인 기능을 코드로 구현하진 않았지만 이 기능은 check 만 하는 것이지 추가 질문이 없을 것 같음.
    //     
    */
    
    if (key == 'E' || key == 'e')
    {
        msg.node_messages = 3;
        msg.sub_index = 1;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
        std::cout<<" "<<std::endl;
        std::cout<<"---------------------SDO controller---------------------- "<<std::endl;
        std::cout<<"Current Status: C, Enable operation: E"<<std::endl;
        std::cout<<"Position mode: P, Velocity mode: V, Torque mode: T"<<std::endl;
        std::cout<<"Set Target: T, quit: Q"<<std::endl;
        std::cout<<"--------------------------------------------------------- "<<std::endl;
        std::cout<<" "<<std::endl;
        std::cin>>key;
        if (key=='q'||key=='Q')
        {
            key2 == 'A';
        }
        
    }

    /*
    //Position mode.
    */
    
    else if (key == 'P'|| key == 'p')
    {   
        std::cout<<"---------------------Position mode---------------------- "<<std::endl;
        std::cout<<"Relative: 'R', Absoulte: 'A'."<<std::endl;
        std::cout<<"For other command, type 'Q'."<<std::endl;
        std::cout<<"--------------------------------------------------------- "<<std::endl;
        std::cout<<" "<<std::endl;
        std::cin>>key2;
        
        if(key2=='r'||key2=='R'||key2=='a'||key2=='A')
        {
            std::cout<<"--------------------------------------------------------- "<<std::endl;
            std::cout<<"Enter a target position."<<std::endl;
            std::cout<<"--------------------------------------------------------- "<<std::endl;
            std::cin>>key3;
        }
        else if(key2=='q'||key2=='Q')
        {
            std::cout<<""<<std::endl;
        }
        else
        {
            ROS_ERROR("Wrong input is written.");
        }
        msg.node_messages = 3;
        msg.sub_index = 2;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }

    /* Velocity mode
    */

    else if (key == 'V'|| key == 'v')
    {   std::cout<<"---------------------Velocity mode---------------------- "<<std::endl;
        std::cout<<"Enter a target velocity."<<std::endl;
        std::cout<<"For other command, type 'Q'."<<std::endl;
        std::cout<<"--------------------------------------------------------- "<<std::endl;
        std::cout<<" "<<std::endl;
        std::cin>>key2;
               
        msg.node_messages = 2;
        msg.sub_index = 2;
        msg.node_num = nodenum;
        ros_tutorial_pub.publish(msg);
    }

    else if (key == 'T'|| key == 't')
    {
        std::cout<<"---------------------Torque mode---------------------- "<<std::endl;
        std::cout<<"Enter a target torque."<<std::endl;
        std::cout<<"For other command, type 'Q'."<<std::endl;
        std::cout<<"--------------------------------------------------------- "<<std::endl;
        std::cout<<" "<<std::endl;
        std::cin>>key2;
        
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

    else if(key == 'Q' || key == 'q')
    {
        return 0;
    }   

loop_rate.sleep();

++count;
}
return 0;
}
