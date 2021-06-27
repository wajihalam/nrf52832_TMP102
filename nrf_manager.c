
//INCLUDES
#include "nrf_manager.h"
#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_temp.h"
#include <stdio.h>

void manager_init(void) 
{

  NRF_LOG_INFO("\tMANAGER CODE STARTED");
  NRF_LOG_FLUSH(); //Limited LOG buffer, so flushing intermittently
  twi_init();      //Initializing twi

  while (1) 
  {
    read_tmp102();           // Reading data from temperature sensor
    bsp_board_led_invert(0); // Visual notification of working of the device.
    nrf_delay_ms(1000);
  }
}
