#include <ros/ros.h>
#include <socketcan_bridge/topic_to_socketcan.h>
#include <socketcan_interface/threading.h>
#include <socketcan_interface/string.h>
#include <string>
#include <can_msgs/Frame.h>
#include <iostream>
#include <socketcan_bridge/canopen_bc_low.h>

int main(int argc,char **argv)
{
    ros::init(argc,argv,"canopen_bc_low");
    ros::NodeHandle nh(""), nh_param("~");
    std::string can_device;
    nh_param.param<std::string>("can_device", can_device, "can0");

    boost::shared_ptr<can::ThreadedSocketCANInterface> driver = boost::make_shared<can::ThreadedSocketCANInterface> ();
    ros::Publisher ros_pub_cantopic = nh.advertise<can_msgs::Frame>("sent_messages",5);
    ros::Rate loop_rate(10);

    while(ros::ok())
    {        
        ROS_INFO("I: initialize / M: Operate mode / T : Target value / R : Read value /F : Stop");

        CAN_keyboard::CANsend cs(int ID, int time); // object 정의 
        //cs.NMT();
        char key; char key2;
        int count2;
        int counta;
        int countb;
        int countc;
        countc=0;
        countb = 0;
        int nodeID;
        int key3;
        std::cin>>key;
        std::cout<<"key: %d"<<key<<std::endl;
        int given_time = 20;

        if (key == 'N')
        {
            //char *mode = "NMT";
            //bool error = false;
            //CAN_keyboard::CANsend::NMT();
            cs.NMT(); // 왜 안돼지!?!?!?!?!?!?!?!?!?!?!?!?!?!??
        }

        /*else if(key == 'I')
        {
            int ID;
            std::cout<<"which node to initialize?"<<std::endl;
            std::cin>>ID;
            CAN_keyboard::CANsend::OP_mode(int ID, char* mode);
        }
        else if(key == 'O')
        {
            cs.OP_mode(int ID, char* mode);
        }

        else if (key == 'T')
        {
            std::cout<<"Current mode is"<<opmode<<std::endl;
            std::cout<<"Which value are you willing to?"<<std::endl;
            std::cin>>tar;
            cs.Target(char* opmode, int tar, int que);
        }

        else if (key == 'G')
        {
            if (opmode == 'P')
            {
                std::cout<<"mode is"<<opmode<<std::endl;
                std::cout<<"relatively? yes(Y) or No(N)"<<std::endl;
                std::cin>>r;
                cs.Go(char* opmode, char* r, int que);
            }
            else
            {
                std::cout<<"mode is"<<opmode<<std::endl;
                r = 'N';
                cs.Go(char* opmode, char* r, int que);
            }
        }
        else if (key == 'R')
        {


        }
        */
        else if (key == 'F')
        {
           return 0; 
        }
    }
}