#include <ros/ros.h>
#include <socketcan_bridge/topic_to_socketcan.h>
#include <socketcan_bridge/socketcan_to_topic.h>
#include <socketcan_interface/threading.h>
#include <socketcan_interface/string.h>
#include <string>
#include <can_msgs/Frame.h>
#include <iostream>

int main(int argc,char **argv)
{
    ros::init(argc,argv,"ros_bc_cantopic");
    ros::NodeHandle nh(""), nh_param("~");
    std::string can_device;
    nh_param.param<std::string>("can_device", can_device, "can0");

    boost::shared_ptr<can::ThreadedSocketCANInterface> driver = boost::make_shared<can::ThreadedSocketCANInterface> ();
    ros::Publisher ros_pub_cantopic = nh.advertise<can_msgs::Frame>("sent_messages",5);

    socketcan_bridge::SocketCANToTopic to_topic_bridge(&nh, &nh_param, driver);
    to_topic_bridge.setup(nh_param);
    
    ros::Rate loop_rate(5);
    char key; char key2;
    int count2;
    int counta;
    int countb;
    int countc;
    countc=0;
    countb = 0;
    int nodeID;
    int key3;
    std::cout<<"Which node to control?"<<std::endl;
    std::cin>>nodeID;
    // 2. Set the driving mode // "M" "P" "V" "C" // Mode / position / velocity / current

    // 3.1 Target value for each driving mode // "T" "1000" - target / target value

    // 3.2 Read current value // "R" -> "p" "v" "c" //
    // 4. Emergency stop // "E" - emergency

    // 5. Change the driving mode // "D" - drive mode

    // 6. Finish the connection //  "F"

    while(ros::ok())
        {
            ROS_INFO("I: initialize / M: Operate mode / T : Target value / R : Read value /F : Stop");
            std::cin>>key;
            std::cout<<"pressed key: %c"<<key<<std::endl;
            key2 = 'P';
            // 1. Initiate the motor driver // "I"
            if (key == 'I'){
                    counta = 0;
                    while (counta<20)
                        {
                            if(counta == 3){
                                    can_msgs::Frame msg;
                                    msg.id = 000;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 2;
                                    msg.data[0] = 128;msg.data[1] = 02;msg.data[2] = 00;msg.data[3] = 00;
                                    msg.data[4] = 00; msg.data[5] = 00;msg.data[6] = 00;msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("Request nodes to enter pre-operational mode.");
                                }
                            else if(counta == 5){
                                    can_msgs::Frame msg;
                                    msg.id = 000;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 2;
                                    msg.data[0] = 129;msg.data[1] = 02;msg.data[2] = 00;msg.data[3] = 00;
                                    msg.data[4] = 00; msg.data[5] = 00;msg.data[6] = 00;msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("Request nodes to reset");
                                 }
                            else if(counta == 7){
                                    can_msgs::Frame msg;
                                    msg.id = 000;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 2;
                                    msg.data[0] = 130; msg.data[1] = 02; msg.data[2] = 00; msg.data[3] = 00;
                                    msg.data[4] = 00;  msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("Request nodes to reset communication.");
                                }
                            else if(counta == 9){
                                    can_msgs::Frame msg;
                                    msg.id = 000;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 2;
                                    msg.data[0] = 01; msg.data[1] = 02; msg.data[2] = 00; msg.data[3] = 00;
                                    msg.data[4] = 00; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("Request nodes to enter operational mode.");
                                 }
                            else if(counta == 11){
                                    can_msgs::Frame msg;
                                    msg.id = 1538;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 8;
                                    msg.data[0] = 43; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                    msg.data[4] = 06; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("Set Node2 Position mode(1/3)");
                                }
                            else if(counta == 13){
                                    can_msgs::Frame msg;
                                    msg.id = 1538;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 8;
                                    msg.data[0] = 43; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                    msg.data[4] = 07; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("Set Node2 Position mode(2/3)");
                                }
                            else if(counta == 15){
                                    can_msgs::Frame msg;
                                    msg.id = 1538;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 8;
                                    msg.data[0] = 43; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                    msg.data[4] = 15; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("Set Node2 Position mode(3/3)");
                                 }
                            else if(counta == 17){
                                    can_msgs::Frame msg;
                                    msg.id = 1538;
                                    msg.is_rtr = false;
                                    msg.is_extended = false;
                                    msg.is_error = false;
                                    msg.dlc = 8;
                                    msg.data[0] = 47; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                    msg.data[4] = 01; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                    ros_pub_cantopic.publish(msg);
                                    ROS_INFO("set position mode finished.");
                                }
                            else if (counta == 18){
                                    ROS_INFO("Initialized");
                                }
                            loop_rate.sleep();
                            counta++;
                        }
                }
            else if(key == 'M'){
                    std::cout<<"Which mode? P: position / V: Velocity / C : current"<<std::endl;
                    std::cin>>key2;
                    if (key2 == 'P'){
                            countb=0;
                            while(countb < 6){
                                    if(countb == 2){
                                            can_msgs::Frame msg;
                                            msg.id = 1538;
                                            msg.is_rtr = false;
                                            msg.is_extended = false;
                                            msg.is_error = false;
                                            msg.dlc = 8;
                                            msg.data[0] = 47; msg.data[1] = 96; msg.data[2] = 96; msg.data[3] = 00;
                                            msg.data[4] = 01; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                            ros_pub_cantopic.publish(msg);
                                            ROS_INFO("Position mode enabled(1/2)");}
                                        else if(countb==4){
                                            can_msgs::Frame msg;
                                            msg.id = 1538;
                                            msg.is_rtr = false;
                                            msg.is_extended = false;
                                            msg.is_error = false;
                                            msg.dlc = 8;
                                            msg.data[0] = 64; msg.data[1] = 97; msg.data[2] = 96; msg.data[3] = 00;
                                            msg.data[4] = 00; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                            ros_pub_cantopic.publish(msg);
                                            ROS_INFO("Position mode enabled(2/2)");}
                                    countb++;
                                    loop_rate.sleep();
                                }

                        }
                    else if(key2 == 'V'){
                            can_msgs::Frame msg;
                            msg.id = 000;
                            msg.is_rtr = false;
                            msg.is_extended = false;
                            msg.is_error = false;
                            msg.dlc = 8;
                            msg.data[0] = 100;msg.data[1] = 02;msg.data[2] = 00;msg.data[3] = 00;
                            msg.data[4] = 00; msg.data[5] = 00;msg.data[6] = 00;msg.data[7] = 00;
                            ros_pub_cantopic.publish(msg);
                            ROS_INFO("TT2");}
                    else if(key2 == 'C'){
                            can_msgs::Frame msg;
                            msg.id = 000;
                            msg.is_rtr = false;
                            msg.is_extended = false;
                            msg.is_error = false;
                            msg.dlc = 8;
                            msg.data[0] = 100;msg.data[1] = 02;msg.data[2] = 00;msg.data[3] = 00;
                            msg.data[4] = 00; msg.data[5] = 00;msg.data[6] = 00;msg.data[7] = 00;
                            ros_pub_cantopic.publish(msg);
                            ROS_INFO("TT3");}
                    else
                        {
                        std::cout<<"wrong character. Restart."<<std::endl;
                        //error = 1;
                        break;
                        }

                }
            else if(key =='T'){
                    if(key2 == 'P'){
                            std::cout<<"Your current mode is position mode. Which is your target position?"<<std::endl;
                            std::cin>>key3;
                            can_msgs::Frame msg;
                            msg.id = 1538;
                            msg.is_rtr = false;
                            msg.is_extended = false;
                            msg.is_error = false;
                            msg.dlc = 8;
                            msg.data[0] = 35; msg.data[1] = 122; msg.data[2] = 96; msg.data[3] = 00;
                            msg.data[4] = 32; msg.data[5] = 78; msg.data[6] = 00; msg.data[7] = 00;
                            // data 4 & data 5 is related to the target position.
                            ros_pub_cantopic.publish(msg);
                            ROS_INFO("Target position is %d",key3);}
                        }
            else if(key == 'H')
                {
                    countc=0;
                   // ROS_INFO("aa");
                    //if(key2 == 'P'){
                            while(countc<6)
                                {
                                if (countc ==3){
                                        can_msgs::Frame msg;
                                        msg.id = 1538;
                                        msg.is_rtr = false;
                                        msg.is_extended = false;
                                        msg.is_error = false;
                                        msg.dlc = 8;
                                        msg.data[0] = 43; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                        msg.data[4] = 15; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                        ros_pub_cantopic.publish(msg);
                                        ROS_INFO("Go to target position relatively.");}
                                else if (countc == 5){
                                        can_msgs::Frame msg;
                                        msg.id = 1538;
                                        msg.is_rtr = false;
                                        msg.is_extended = false;
                                        msg.is_error = false;
                                        msg.dlc = 8;
                                        msg.data[0] = 43; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                        msg.data[4] = 63; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                        // 63 -> 3F(abs) 95 -> 5F(rel)
                                        ros_pub_cantopic.publish(msg);
                                    }
                                loop_rate.sleep();
                            countc++;
                            //ROS_INFO("kk");
                       // }
                }
                }

            else if(key == 'G')
                {
                    countc=0;
                            while(countc<6)
                                {
                                if (countc ==3){
                                        can_msgs::Frame msg;
                                        msg.id = 1538;
                                        msg.is_rtr = false;
                                        msg.is_extended = false;
                                        msg.is_error = false;
                                        msg.dlc = 8;
                                        msg.data[0] = 43; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                        msg.data[4] = 15; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                        ros_pub_cantopic.publish(msg);
                                        ROS_INFO("Go to target position absolutely.");}
                                else if (countc == 5){
                                        can_msgs::Frame msg;
                                        msg.id = 1538;
                                        msg.is_rtr = false;
                                        msg.is_extended = false;
                                        msg.is_error = false;
                                        msg.dlc = 8;
                                        msg.data[0] = 43; msg.data[1] = 64; msg.data[2] = 96; msg.data[3] = 00;
                                        msg.data[4] = 95; msg.data[5] = 00; msg.data[6] = 00; msg.data[7] = 00;
                                        // 63 -> 3F(abs) 95 -> 5F(rel)
                                        ros_pub_cantopic.publish(msg);
                                    }
                                loop_rate.sleep();
                            countc++;
                                }
                }

            else if(key == 'R'){

                }
            else if(key == 'F'){
                    return 0;
                }

        //count2 = count2+10;
        count2++;
        loop_rate.sleep();
        //ROS_INFO("test2");
}
return 0;
}

//msg.header.seq = 769;
//msg.header.frame_id = 'a';
//int error = 0;
