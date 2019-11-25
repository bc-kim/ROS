#ifndef CAN_TRANS_H
#define CAN_TRANS_H

#include <ros/ros.h>
#include <string>

namespace can_bc
{
class CAN_TRANS
{
  public:
    CAN_TRANS(uint8_t data[8], int* t);
    void Error_code(uint8_t data[8], int* t);
  private:
};
};  
#endif  