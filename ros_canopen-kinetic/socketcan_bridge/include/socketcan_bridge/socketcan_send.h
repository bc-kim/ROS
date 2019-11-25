#ifndef SOCKETCAN_BRIDGE_TOPIC_TO_SOCKETCAN_H
#define SOCKETCAN_BRIDGE_TOPIC_TO_SOCKETCAN_H

#include <socketcan_interface/socketcan.h> // can 패킷에 대한 기본 structure 제시
#include <can_msgs/Frame.h> // message 양식 structure
#include <ros/ros.h> // ros 기본 header

namespace ROS_socketcan_
{
class SocketCAN_TO_ROS
{
  public:
    ModeToSocketCAN(ros::NodeHandle* nh, ros::NodeHandle* nh_param, boost::shared_ptr<can::DriverInterface> driver); //constructor -> used to initialize the class values.
    void setup();

  private:
    ros::Subscriber can_topic_;
    boost::shared_ptr<can::DriverInterface> driver_;

    can::StateInterface::StateListener::Ptr state_listener_;

    void msgCallback(const cansend_msgs::cantopic::ConstPtr& msg);
    void stateCallback(const can::State & s);
};


void convert_M_To_S(const cansend_msgs::cantopic::ConstPtr& msg, can::Frame& f, int i])
{
  char* mode = msg.mode;
  if (mode == Init){
    if(i == 1){
    f.id = 000;
    f.is_rtr = false;
    f.is_extended = false;
    f.is_error = false;
    f.dlc = 2;
    f.data[0] = 128;msg.data[1] = 02;msg.data[2] = 00;msg.data[3] = 00;
    f.data[4] = 00; msg.data[5] = 00;msg.data[6] = 00;msg.data[7] = 00;      
    }
  }

  /*else if (mode == Reset){

  }

  else if (mode == PDO){

    
  }
  f.id = m.id;*/

}

};  // namespace socketcan_bridge


#endif  // SOCKETCAN_BRIDGE_TOPIC_TO_SOCKETCAN_H
