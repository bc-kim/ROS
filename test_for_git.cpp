#include <ros/ros.h>
#include <string>
#include <can_msgs/Frame.h>
#include <iostream>
//#include <ros_can_rx_bc/can_trans.h>
#include "ros_can_rx_bc/msg_FP.h"
#include "ros_can_rx_bc/msg_FP2.h"
#include "ros_can_rx_bc/msg_FP3.h"
#include "ros_can_rx_bc/msg_FP4.h"
#include "ros_can_rx_bc/msg_Error.h"
aaaa
class CanToNode
{
public:
    // Constructor
    CanToNode()
    {
        pub_ = n.advertise<ros_can_rx_bc::msg_FP>("msg_Force_position",1);
        sub_ = n.subscribe<can_msgs::Frame>("received_messages",1,&CanToNode::callback,this);
    }

    // Call back function: When CAN message is received, this function works.
    void callback(const can_msgs::Frame::ConstPtr& input)
    {
        if(input->id>0x80&&input->id<0x90 && input->dlc==5)  // Check error Data.
        {
            for (int i = 0; i < 8; i++)
            {
                Senddata[i]=input->data[i];
            }
            //can_bc::CAN_TRANS Trans_data(Senddata, &t);
            ROS_INFO("Node ID: %d", id);
            ROS_INFO("Error code: %d",t);
            id = input->id - 0x80;
            //output.errorcode = t;
            //pub_.publish(output);
        }
    }

    // Variables
    ros_can_rx_bc::msg_FP output;
    
    uint8_t Senddata[8];
    int t;
    int Force_T1;
    int Position_T1;
    int Force_T2;
    int Position_T2;
    int Force_I;
    int Position_I;
    int id;

private:
    ros::NodeHandle n;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    
};

int main(int argc,char **argv)
{
    ros::init(argc,argv,"ros_can_rx_bc_node");
    ROS_INFO("ROS_CAN_Translator_enabled");
    CanToNode CANTONODE; // if u wants to access force data, than CANTOPFOBJ.Force can be used.
    ros::spin();
    return 0;
}
