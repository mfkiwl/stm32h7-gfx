#include "ap.h"
#include "thread.h"
#include "touchgfx.h"




void apInit(void)
{  
  thread::init();

  touchgfxInit();
}

void apMain(void)
{
  uint32_t pre_time;


  pre_time = millis();
  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      ledToggle(_DEF_LED1);
    }    
    sdUpdate();
    delay(10);
  }
}

