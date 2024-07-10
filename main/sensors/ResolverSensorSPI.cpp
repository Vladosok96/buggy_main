#include "ResolverSensorSPI.h"
#include "esp_log.h"

static const char* TAG = "TAMAGAWA resolver";


ResolverSensorSPI::ResolverSensorSPI(spi_device_handle_t* spiHandler){
  this->spiHandler = spiHandler;
  resTrans.length = 16;
  resTrans.flags = SPI_TRANS_USE_RXDATA | SPI_TRANS_USE_TXDATA;
}


void ResolverSensorSPI::init(){
  this->Sensor::init(); // call base class init
}

bool ResolverSensorSPI::checkBitParity(uint16_t num) {
    num ^= num >> 1;
    num ^= num >> 2;
    num = (num & 0x1111U) * 0x1111U;
    return (num >> 12) & 1;
}

//  Shaft angle calculation
//  angle is in radians [rad]
float ResolverSensorSPI::getSensorAngle(){
  spi_device_transmit(*spiHandler, &resTrans);
  uint16_t angle = resTrans.rx_data[0];
  angle |= (uint16_t)(resTrans.rx_data[1] & 0b00001111) << 8;
  if (checkBitParity(angle) != (bool)(resTrans.rx_data[1] & 0b00010000)) {
      ESP_LOGE(TAG, "Resolver decoder angle parity check failed!");
  }
  // ESP_LOGI(TAG, "%d", angle);
  return ((float)angle) / 4095.0 * _2PI;
}
