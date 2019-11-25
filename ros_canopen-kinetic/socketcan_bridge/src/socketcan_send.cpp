#include <socketcan_bridge/socketcan_send.h>
#include <socketcan_interface/string.h>
#include <string>
#include <iostream>
#include <ros/ros.h>
namespace socketcan_send
{
  ModeToSocketCAN::ModeToSocketCAN(ros::NodeHandle* nh, ros::NodeHandle* nh_param,
      boost::shared_ptr<can::DriverInterface> driver) // Constructor for "topic to socket can" class.
    {
      can_topic_ = nh->subscribe<cansend_msgs::cantopic>("sent_messages", 1,
                    boost::bind(&ModeToSocketCAN::msgCallback, this, _1));
      driver_ = driver;
      ROS_INFO("ROS_CAN_Subscriber_enabled");
    };

  void ModeToSocketCAN::setup()
    {
      state_listener_ = driver_->createStateListener(
              can::StateInterface::StateDelegate(this, &ModeToSocketCAN::stateCallback));
      ROS_INFO("ROS_CAN_Subscriber_initiated");
    };

  void ModeToSocketCAN::msgCallback(const cansend_msgs::cantopic::ConstPtr& msg)
    {
      //This msgCallback 

      //Initial settings//
      ros::Rate loop_rate(10);
      ROS_INFO("TOPIC_RECEIVED");
      int i = msg.num; // number of can messages to send.
      int cnt = 0;

      //convert topic to can messages.//
      while(cnt<i){
        can::Frame f;
        convert_M_To_S(msg, f, cnt);// converts the can_msgs::Frame (ROS msg) to can::Frame (socketcan.h)
        if (!f.isValid()){  // check if the id and flags are appropriate.
          ROS_ERROR("Invalid frame from topic: id: %#04x, length: %d, is_extended: %d", f.id, f.dlc, f.is_extended);
          return;}
        bool_res = driver_-> send(f); // send f using can driver
        if (res){
           ROS_INFO("ROS_CAN_well_sent");}
        else if (!res){
          ROS_ERROR("Failed to send message: %s.", can::tostring(f, true).c_str());}
        // wait for the answer //


        cnt++;
        loop_rate.sleep();}
    };

  void ModeToSocketCAN::stateCallback(const can::State & s)
    {
      std::string err;
      ROS_INFO("state_callback");
      driver_->translateError(s.internal_error, err);
      if (!s.internal_error)
      {
        ROS_INFO("State: %s, asio: %s", err.c_str(), s.error_code.message().c_str());
      }
      else
      {
        ROS_ERROR("Error: %s, asio: %s", err.c_str(), s.error_code.message().c_str());
      }
    };
};  // namespace socketcan_bridge

