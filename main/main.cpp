#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_eth.h"
#include "Ethernet.h"
#include "Webserver.h"
#include "NVStorage.h"

static const char* TAG = "main";

extern "C" void app_main(void) {
    NVStorage::init();
    NVStorage::loadSystemParams();
    Ethernet::init(40, 41, 2, 42, 1, SPI3_HOST);
    Webserver::init();
}