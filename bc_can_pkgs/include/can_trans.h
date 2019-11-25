#ifndef CAN_TRANS_H
#define CAN_TRANS_H

#include <ros/ros.h>
#include <string>

namespace can_trans
{
class CAN_TRANS
{
  public:
    CAN_TRANS(uint8_t Errordata[5]);
    int check(uint8_t Errordata[5]);
    std::string check_s(uint8_t Errordata[5]);
  private:
};
};  
#endif  