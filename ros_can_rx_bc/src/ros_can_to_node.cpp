/* This node reads CAN data and sends current status to CAN_status_reade_node.
// This node reads 
// 1. NMT condition
// 2. Operation mode of the motor(position, velocity, torque, )
// 3. Error. (0x80 error)
// 4. 
*/

#include <ros/ros.h>
#include <string>
#include <can_msgs/Frame.h>
#include <iostream>
#include <ros_can_rx_bc/can_trans.h>
#include "ros_can_rx_bc/msg_to_topic.h"

class CanToNode
{
public:
    // Constructor
    CanToNode()
    {
        pub_ = n.advertise<ros_can_rx_bc::msg_to_topic>("msg_to_topic",1);
        sub_ = n.subscribe<can_msgs::Frame>("received_messages",1,&CanToNode::callback,this);
    }

    // Call back function: When CAN message is received, this function works.
    void callback(const can_msgs::Frame::ConstPtr& input)
    {
        for (int i = 0; i < 8; i++)
        {
            sentdata[i]=input->data[i];
        }
        ID = input->id;
        DLC = input->dlc;

        if(ID>0x80&&ID<0x90 && DLC==5)  // Check error Data.
        {    
            can_bc::CAN_TRANS Translate_data(sentdata, &error_code);
            Node_number = ID - 0x80;
            ROS_INFO("Node number: %d", Node_number);
            ROS_INFO("Error code: %d",error_code);
            output.msg_to_nodes = 1;
            output.sub_index = error_code;
        }

        else if(ID>0x700&&ID<0x710 && DLC == 1) // NMT status
        {
            Node_number = ID - 0x700;
            output.msg_to_nodes = 2; 
            output.node_num = Node_number;
            if(sentdata[0]==0x05 || sentdata[0]==0x85) //node is operational
            {
                output.sub_index = 1;
            }
            else if(sentdata[0]==0x04 || sentdata[0]==0x84) //node is stopped
            {
                output.sub_index = 2;
            }
            else if(sentdata[0]==0x7F || sentdata[0]==0xFF) //node is pre-opearational
            {
                output.sub_index = 3;
            }
        }

        else if(ID==0x500) // operation mode of the motor
        {

        }
        pub_.publish(output);
        output.msg_to_nodes = 0;
        output.sub_index = 0;

    }

    // Variables
    ros_can_rx_bc::msg_to_topic msg_to_nodes;
    uint8_t sentdata[8];
    ros_can_rx_bc::msg_to_topic output;
    int Node_number;
    int error_code;
    int ID;
    int DLC;

private:
    ros::NodeHandle n;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    
};

int main(int argc,char **argv)
{
    ros::init(argc,argv,"ros_can_to_topic_node");
    ROS_INFO("ROS_CAN_Translator_enabled");
    CanToNode CANTONODE; // if u wants to access force data, than CANTOPFOBJ.Force can be used.
    ros::spin();
    return 0;
}
