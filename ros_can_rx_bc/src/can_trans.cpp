#include <string>
#include <ros_can_rx_bc/can_trans.h>
#include <ros/ros.h>

namespace can_bc
{
  CAN_TRANS::CAN_TRANS(uint8_t data[8], int* t)
    {
        ROS_INFO("CAN error_message: [%02x][%02x][%02x][%02x][%02x]",data[0],data[1],data[2],data[3],data[4]);
        if (data[0] == 0x00 && data[1] == 0x00)
        {
            ROS_INFO("No error");
            *t = 0;
        }

        else if(data[0] == 0x10 && data[1] == 0x32)
        {
            ROS_INFO("Overvoltage");
            *t = 1;
        }

        else if(data[0] == 0x20 && data[1] == 0x32)
        {
            ROS_INFO("Undervoltage");
            *t = 2;
        }
        
        else if(data[0] == 0xF0 && data[1] == 0x43)
        {
            ROS_INFO("Temperature warning");
            *t = 3;
        }
        
        else if(data[0] == 0x10 && data[1] == 0x43)
        {
            ROS_INFO("Temperature Error");
            *t = 4;
        }
        
        else if(data[0] == 0x10 && data[1] == 0x54)
        {
            ROS_INFO("Outputstages");
            *t = 5;
        }        
        
        else if(data[0] == 0x30 && data[1] == 0x55)
        {
            ROS_INFO("EEPROM fault");
            *t = 6;
        }        
        else if(data[0] == 0x00 && data[1] == 0x61)
        {
            ROS_INFO("Software error");
            *t = 7;
        }

        else if(data[0] == 0x00 && data[1] == 0x72)
        {
            ROS_INFO("Measurement circuit: Current measurement");
            *t = 7;
        }
        else if(data[0] == 0x00 && data[1] == 0x73)
        {
            ROS_INFO("Software error");
            *t = 7;
        }
        else if(data[0] == 0x00 && data[1] == 0x74)
        {
            ROS_INFO("Software error");
            *t = 7;
        }
        else if(data[0] == 0x10 && data[1] == 0x81)
        {
            ROS_INFO("Software error");
            *t = 7;
        }
        else if(data[0] == 0x30 && data[1] == 0x81)
        {
            ROS_INFO("Software error");
            *t = 7;
        }
        else if(data[0] == 0x40 && data[1] == 0x81)
        {
            ROS_INFO("Software error");
            *t = 7;
        }
        else if(data[0] == 0x10 && data[1] == 0x83)
        {
            ROS_INFO("Software error");
            *t = 7;
        }
        else if(data[0] == 0xF0 && data[1] == 0x84)
        {
            ROS_INFO("Software error");
            *t = 7;
        }

        else if(data[0] == 0xFF && data[1] == 0x84)
        {
            ROS_INFO("Software error");
            *t = 7;
        }

        else if(data[0] == 0x11 && data[1] == 0x86)
        {
            ROS_INFO("Software error");
            *t = 7;
        }

        else
        {
            ROS_INFO("Unregistered error");
            *t = 99;
        }
        
    };

    void CAN_TRANS::Error_code(uint8_t data[8], int* t)
    {
        *t = 2;

    };
};  // namespace socketcan_bridge
