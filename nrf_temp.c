#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf_delay.h"
#include "nrf_drv_twi.h"
#include "stdint.h"
#include <stdio.h>
//#include "bsp.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_manager.h"
#include "nrf_temp.h"

#define TMP_ADDRESS (0x48) // Temp102 sensor I2C address
/* TWI instance ID. */
#define TWI_INSTANCE_ID 0
/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/**
 * @brief TWI initialization.
 */
void twi_init(void) 
{
  ret_code_t err_code;

  const nrf_drv_twi_config_t twi_config = {
      .scl = ARDUINO_SCL_PIN,
      .sda = ARDUINO_SDA_PIN,
      .frequency = NRF_DRV_TWI_FREQ_100K,
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
      .clear_bus_init = false};

  err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
  APP_ERROR_CHECK(err_code);

  nrf_drv_twi_enable(&m_twi);
}

/**
* @brief read TMP102 temperature
*/
void read_tmp102(void) 
{
  uint8_t tmp_data[2];
  uint8_t tmp_data_le[2];
  uint16_t *tmp = (uint16_t *)&tmp_data_le[0];

  nrf_drv_twi_rx(&m_twi, TMP_ADDRESS, tmp_data, 2);

  tmp_data_le[0] = tmp_data[1];
  tmp_data_le[1] = tmp_data[0];
  float tmp102 = (*tmp >> 4) * 0.0625;

  NRF_LOG_INFO("DATA: 0x%x, 0x%x", tmp_data[0], tmp_data[1]);
  NRF_LOG_INFO("TMP: " NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT(tmp102));
  NRF_LOG_FLUSH();
}