#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf_drv_twi.h"
#include <stdio.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_manager.h"
#include "nrf_temp.h"

/**
 * @brief Function for main application entry.
 */
int main(void) {
  ret_code_t err_code;

  APP_ERROR_CHECK(NRF_LOG_INIT(NULL)); //Initializing Logger
  NRF_LOG_DEFAULT_BACKENDS_INIT();
  bsp_board_init(BSP_INIT_LEDS);       //Initializng LEDs
 
  NRF_LOG_INFO("Temperature scanner started.");
  NRF_LOG_FLUSH();

  manager_init();                      //Main Manager function
}

/** @} */