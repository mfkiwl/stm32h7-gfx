#include "touchgfx.h"

#include <common/TouchGFXInit.hpp>
#include <touchgfx/hal/BoardConfiguration.hpp>
#include <touchgfx/hal/GPIO.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <platform/driver/lcd/LCD24bpp.hpp>

#include <STM32H7DMA.hpp>
#include <STM32H7HAL.hpp>

#include <STM32H7TouchController.hpp>
#include <STM32H7Instrumentation.hpp>



static LCD16bpp display;
static uint16_t bitDepth = 16;





bool touchgfxInit(void)
{
  STM32H7DMA *dma = new STM32H7DMA;
  STM32H7TouchController *tc = new STM32H7TouchController;
  STM32H7Instrumentation *mcuInstr = new STM32H7Instrumentation;

  uint16_t dispWidth  = HW_LCD_WIDTH;
  uint16_t dispHeight = HW_LCD_HEIGHT;


  HAL& hal = touchgfx_generic_init<STM32H7HAL>(*dma, display, *tc, dispWidth, dispHeight,
                                                (uint16_t*)bmpCache, BMP_CACHE_SIZE, 128);

  hal.setFrameBufferStartAddress((uint16_t*)frameBuf0, bitDepth, true, true);

  hal.setTouchSampleRate(1);
  hal.setFingerSize(1);
  hal.setButtonController(&btnCtrl);
  // By default frame rate compensation is off.
  // Enable frame rate compensation to smooth out animations in case there is periodic slow frame rates.
  hal.setFrameRateCompensation(false);

  // This platform can handle simultaneous DMA and TFT accesses to SDRAM, so disable lock to increase performance.
  hal.lockDMAToFrontPorch(false);

  mcuInstr->init();

  //Set MCU instrumentation and Load calculation
  hal.setMCUInstrumentation(mcuInstr);
  hal.enableMCULoadCalculation(true);

  return true;
}