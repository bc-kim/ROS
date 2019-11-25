/* This node reads topic from other nodes and sends CAN message to specific device.
// This node handles
// 1. NMT check
// 2. NMT operate
// 3. Change the operation mode of the motor (position, velocity, torque, )
// 4. Emergency stop
// 5. Operate STM chip.
*/

#include <ros/ros.h>
#include <socketcan_bridge/topic_to_socketcan.h>
#include <socketcan_bridge/socketcan_to_topic.h>
#include <socketcan_interface/threading.h>
#include <socketcan_interface/string.h>
#include <string>
#include <can_msgs/Frame.h>
#include "can_msgs/Node_msgs.h"
#include <iostream>
class CAN_TO_NODE
{
    public:
    //constructor
    CAN_TO_NODE()
    {
        pub_ = n.advertise<can_msgs::Frame>("sent_messages",1); // Error data
        sub_ = n.subscribe<can_msgs::Frame>("received_messages",1,&CAN_TO_NODE::callback,this);
        sub_2 = n.subscribe<can_msgs::Node_msgs>("node_messages",1,&CAN_TO_NODE::callback2,this);
    }

    void callback(const can_msgs::Frame::ConstPtr& input) // Directly get data from CAN
    {
        if(input->id==0x52)
        {
            /*ROS_INFO("Force_data_received");
            can_msgs::Frame msg;
            msg.id = 000;
            msg.is_rtr = false;
            msg.is_extended = false;
            msg.is_error = false;
            msg.dlc = 2;
            msg.data[0] = 128;msg.data[1] = 02;msg.data[2] = 00;msg.data[3] = 00;
            msg.data[4] = 00; msg.data[5] = 00;msg.data[6] = 00;msg.data[7] = 00;
            CAN_TO_NODE::pub_.publish(msg);
            */
           flag = 0;
        }
    }

    void callback2(const can_msgs::Node_msgs::ConstPtr& input_node) // input from other nodes
    {
        i = input_node->node_messages;
        j = input_node->sub_index;
        node_number = input_node->node_num;
        can_msgs::Frame msg;
        
        if(flag == 0)
        {ROS_INFO("Message sent well");}
        else if(flag==1){ROS_INFO("Resend the message.");}

        if(i == 1)
        {
            ROS_INFO("ROS-to-Device: Check NMT");
            msg.id = 0x700+node_number;
            msg.is_rtr = true;
            msg.is_extended = false;
            msg.is_error = false;
            CAN_TO_NODE::pub_.publish(msg);
        }

        else if(i==2)
        {
            ROS_INFO("ROS-to-Device: NMT");
            if(j==1)
            {
                ROS_INFO("Start remote node indication");
                msg.id = 0x000;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 01; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==2)
            {
                ROS_INFO("Enter Pre-operational state indication");
                msg.id = 0x000;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 128; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==3)
            {
                ROS_INFO("Stop remote node indication");
                msg.id = 0x000;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 2; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==4)
            {
                ROS_INFO("Reset node indication");
                msg.id = 0x000;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 129; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }

            else if(j==5)
            {
                ROS_INFO("Reset communication indication");
                msg.id = 0x000;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 130; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else
            {
                ROS_INFO("ROS-to-Device: NMT-Unidentified sub index");
            }
            
        }

        else if(i==3)
        {
            if(j==1)
            {
                ROS_INFO("ROS-to-Device: Enable motor operation");
                msg.id = 0x600+node_number;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 8;
                msg.data[0] = 0x40; msg.data[1] = 0x41; msg.data[2] = 0x60; msg.data[3] = 0x00;
                msg.data[4] = 0x00; msg.data[5] = 0x00; msg.data[6] = 0x00; msg.data[7] = 0x00;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==2)
            {
                ROS_INFO("ROS-to-Device: Change the opeartion mode of the motor (Pos_mode)");
                msg.id = 0x600+node_number;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 8;
                msg.data[0] = 0x2F; msg.data[1] = 0x60; msg.data[2] = 0x60; msg.data[3] = 0x00;
                msg.data[4] = 0x01; msg.data[5] = 0x00; msg.data[6] = 0x00; msg.data[7] = 0x00;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==2)
            {
                ROS_INFO("ROS-to-Device: Change the opeartion mode of the motor (Vel_mode)");
                msg.id = 0x600+node_number;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 8;
                msg.data[0] = 0x2F; msg.data[1] = 0x60; msg.data[2] = 0x60; msg.data[3] = 0x00;
                msg.data[4] = 0x03; msg.data[5] = 0x00; msg.data[6] = 0x00; msg.data[7] = 0x00;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==3)
            {
                ROS_INFO("ROS-to-Device: Change the opeartion mode of the motor (Torque_mode)");
                msg.id = 0x600+node_number;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 8;
                msg.data[0] = 0x2F; msg.data[1] = 0x60; msg.data[2] = 0x60; msg.data[3] = 0x00;
                msg.data[4] = 0x03; msg.data[5] = 0x00; msg.data[6] = 0x00; msg.data[7] = 0x00;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==2)
            {
                ROS_INFO("ROS-to-Device: Set target position");
                msg.id = 0x600+node_number;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 8;
                msg.data[0] = 0x23; msg.data[1] = 0x7A; msg.data[2] = 0x60; msg.data[3] = 0x00;
                //아래 네 메시지가 target position이 됨.
                msg.data[4] = 0x03; msg.data[5] = 0x00; msg.data[6] = 0x00; msg.data[7] = 0x00;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else{
                ROS_INFO("ROS-to-Device: NMT-Unidentified sub index");
            }
        }

        else if(i==4)
        {
            ROS_INFO("ROS-to-Device: Emergency stop");
        }

        else if(i==5)
        {
            flag = 1;
            
            if(j==1)
            {
                ROS_INFO("Commun. with STM: check status");
                msg.id = 0x051;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 0x01; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==2)
            {
                ROS_INFO("Commun. with STM: Begin operation");
                msg.id = 0x051;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 0x02; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }
            else if(j==3)
            {
                ROS_INFO("Commun. with STM: Set a position mode");
                
                msg.id = 0x051;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 0x03; msg.data[1] = 0x00;
                CAN_TO_NODE::pub_.publish(msg);
            }

            else if(j==4)
            {
                ROS_INFO("Commun. with STM: Set a velocity mode");
                
                /* velocity target을 여기서 바꾸는 것이 의미 없어서 STM단으로 넘김.
                // 만약 두 메시지가 딜레이 없이 보내졌으면 이 부분을 살렸을텐데 딜레이 없이 두 메시지를 
                // 보내면 뒤 메시지만 감..
                msg.id = 0x600+node_number;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 8;
                msg.data[0] = 0x2F; msg.data[1] = 0x60;msg.data[2] = 0x60; msg.data[3] = 0x00;
                msg.data[4] = 0x03; msg.data[5] = 0x00;msg.data[6] = 0x00; msg.data[7] = 0x00;
                CAN_TO_NODE::pub_.publish(msg);
                */
                
                msg.id = 0x051;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 0x04; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }

            else if(j==5)
            {
                ROS_INFO("Commun. with STM: Set a torque mode");
                msg.id = 0x051;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 2;
                msg.data[0] = 0x05; msg.data[1] = node_number;
                CAN_TO_NODE::pub_.publish(msg);
            }
        
            else if(j==6)
            {
                ROS_INFO("Commun. with STM: Set target value");

                msg.id = 0x051;
                msg.is_rtr = false;
                msg.is_extended = false;
                msg.is_error = false;
                msg.dlc = 5;
                msg.data[0] = 0x05; // 혹시 몰라 sub index 용으로 만들어 둠.
                msg.data[1] = input_node->can_msg1;
                msg.data[2] = input_node->can_msg2;
                msg.data[3] = input_node->can_msg3;
                msg.data[4] = input_node->can_msg4;

                CAN_TO_NODE::pub_.publish(msg);
            }
        }
        else
        {
            ROS_INFO("Unknown messages from other nodes.");
        }
    }

    int i;
    int j;
    int node_number;
    int flag;

    private:
    //boost::shared_ptr<can::ThreadedSocketCANInterface> driver = boost::make_shared<can::ThreadedSocketCANInterface> ();
    ros::NodeHandle n;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    ros::Subscriber sub_2;
};


int main(int argc,char **argv)
{
    ros::init(argc,argv,"ros_bc_cantopic_node");
    ros::NodeHandle nh(""), nh_param("~");
    std::string can_device;
    nh_param.param<std::string>("can_device", can_device, "can0");
    CAN_TO_NODE Can_To_node;
    ros::spin();
    return 0;
}
