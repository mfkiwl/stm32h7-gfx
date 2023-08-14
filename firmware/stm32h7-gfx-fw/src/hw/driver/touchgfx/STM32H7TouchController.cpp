
#include "STM32H7TouchController.hpp"
#include "hw.h"



using namespace touchgfx;

void STM32H7TouchController::init()
{
}

bool STM32H7TouchController::sampleTouch(int32_t& x, int32_t& y)
{
  touch_info_t info;


  touchGetInfo(&info);

  if (info.count > 0)
  {
    x = info.point[0].x;
    y = info.point[0].y;   
    return true;
  }

  return false;
}
