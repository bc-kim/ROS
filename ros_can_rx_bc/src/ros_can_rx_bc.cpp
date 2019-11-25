/* socketcan으로부터 CAN message를 받아서 force data일 경우 force data 수집하는 node로 보내고
// error message일 경우 error를 출력하는 node
*/

#include <ros/ros.h>
#include <string>
#include <can_msgs/Frame.h>
#include <iostream>
#include <ros_can_rx_bc/can_trans.h>
#include "ros_can_rx_bc/msg_FP.h"
#include "ros_can_rx_bc/msg_FP2.h"
#include "ros_can_rx_bc/msg_FP3.h"
#include "ros_can_rx_bc/msg_FP4.h"
#include "ros_can_rx_bc/msg_Error.h"

class CanToFP
{
public:
    // Constructor
    CanToFP()
    {
        pub_ = n.advertise<ros_can_rx_bc::msg_FP>("msg_Force_position",1); // Thumb data
        pub_2 = n.advertise<ros_can_rx_bc::msg_FP2>("msg_Force_position2",1); // Index data
        pub_3 = n.advertise<ros_can_rx_bc::msg_FP3>("msg_Force_position3",1); // Index data
        pub_4 = n.advertise<ros_can_rx_bc::msg_FP4>("msg_Force_position4",1); // Index data
        pub_5 = n.advertise<ros_can_rx_bc::msg_Error>("msg_Error",1); // Error data
        sub_ = n.subscribe<can_msgs::Frame>("received_messages",1,&CanToFP::callback,this);
    }

    // Call back function: When CAN message is received, this function works.
    void callback(const can_msgs::Frame::ConstPtr& input)
    {
        if(input->id==0x50 && input->data[0]==0x02 && input->dlc==3) // Load cell 1 Data
        {
             Force_T1 = (256*input->data[2]+input->data[1]);
             output.Force_T1 = Force_T1;
             output.Position_T1 = 0;
             output.Force_T2 = 0;
             output.Position_T2 = 0;
             pub_.publish(output);
        }
        else if(input->id==0x50 && input->data[0]==3 && input->dlc==3) // Load cell 2 Data
        {
            Force_I = 256*input->data[2]+input->data[1];
            output2.Force_I = Force_I;
            pub_2.publish(output2);
        }
        else if(input->id==0x50 && input->data[0]==4 && input->dlc==3) // Load cell 3 Data
        {
            Force_T2 = 256*input->data[2]+input->data[1];
            output3.Force_C = Force_T2;
            pub_3.publish(output3);
        }
        else if(input->id==0x50 && input->data[0]==5 && input->dlc==3) // Load cell 4 Data
        {
            Position_T2 = 256*input->data[2]+input->data[1];
            output4.Force_D = Position_T2;
            pub_4.publish(output4);
        }

        else if(input->id>0x80&&input->id<0x90)  // Check error Data.
        {
            for (int i = 0; i < 8; i++)
            {
                Senddata[i]=input->data[i];
            }
            can_bc::CAN_TRANS Trans_data(Senddata, &t);
            ROS_INFO("Node ID: %d", id);
            ROS_INFO("Error code: %d",t);
            id = input->id - 0x80;
            output5.errorcode = t;
            pub_5.publish(output5);
        }
        else if(input->id>0x580 && input->id<0x599)  // Check error Data.
        {
            ROS_INFO("Motor_driver_data_received");
            pub_5.publish(output5);
        }

    }

    // Variables
    ros_can_rx_bc::msg_FP output;
    ros_can_rx_bc::msg_FP2 output2;
    ros_can_rx_bc::msg_FP3 output3;
    ros_can_rx_bc::msg_FP4 output4;
    ros_can_rx_bc::msg_Error output5;
    
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
    ros::Publisher pub_2;
    ros::Publisher pub_3;
    ros::Publisher pub_4;
    ros::Publisher pub_5;
    ros::Subscriber sub_;
    
};

int main(int argc,char **argv)
{
    ros::init(argc,argv,"ros_can_rx_bc_node");
    ROS_INFO("ROS_CAN_Translator_enabled");
    CanToFP CANTOFPOBJ; // if u wants to access force data, than CANTOPFOBJ.Force can be used.
    ros::spin();
    return 0;
}
