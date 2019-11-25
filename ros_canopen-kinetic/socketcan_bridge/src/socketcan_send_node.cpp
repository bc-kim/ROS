#include <ros/ros.h>
#include <socketcan_bridge/socketcan_send.h>
#include <socketcan_interface/threading.h>
#include <socketcan_interface/string.h>
#include <string>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "socketcan_send_node");

  ros::NodeHandle nh(""), nh_param("~");

  std::string can_device;
  nh_param.param<std::string>("can_device", can_device, "can0");

  boost::shared_ptr<can::ThreadedSocketCANInterface> driver = boost::make_shared<can::ThreadedSocketCANInterface> ();

  if (!driver->init(can_device, 0))  // initialize device at can_device, 0 for no loopback.
  {
    ROS_FATAL("Failed to initialize can_device at %s", can_device.c_str());
    return 1;
  }
    else
  {
    ROS_INFO("Successfully connected to %s.", can_device.c_str());
  }
  socketcan_send::ModeToSocketCAN to_socketcan(&nh, &nh_param, driver); // define socketcan send constructer
  to_socketcan.setup(); // initialization of the socket can send.

  ros::spin();

  driver->shutdown();
  driver.reset();

  ros::waitForShutdown();
}

// namespace 는 socketcan_send로 하고 
