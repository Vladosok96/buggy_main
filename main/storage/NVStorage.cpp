#include "NVStorage.h"

static const char *TAG = "NVStorage";


void NVStorage::init(){
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
}

void NVStorage::loadSystemParams(){
    esp_err_t err;
    nvs_handle_t nvs_handler;
    err = nvs_open("storage", NVS_READWRITE, &nvs_handler);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG,"Reading system params from NVS ...");

        nvs_get_i8(nvs_handler, "dhcp", (int8_t*)&systemParams.dhcp);
        nvs_get_i8(nvs_handler, "ip1", (int8_t*)&systemParams.ip[0]);
        nvs_get_i8(nvs_handler, "ip2", (int8_t*)&systemParams.ip[1]);
        nvs_get_i8(nvs_handler, "ip3", (int8_t*)&systemParams.ip[2]);
        nvs_get_i8(nvs_handler, "ip4", (int8_t*)&systemParams.ip[3]);
        nvs_get_i8(nvs_handler, "ma1", (int8_t*)&systemParams.mask[0]);
        nvs_get_i8(nvs_handler, "ma2", (int8_t*)&systemParams.mask[1]);
        nvs_get_i8(nvs_handler, "ma3", (int8_t*)&systemParams.mask[2]);
        nvs_get_i8(nvs_handler, "ma4", (int8_t*)&systemParams.mask[3]);
        nvs_get_i8(nvs_handler, "gw1", (int8_t*)&systemParams.gateway[0]);
        nvs_get_i8(nvs_handler, "gw2", (int8_t*)&systemParams.gateway[1]);
        nvs_get_i8(nvs_handler, "gw3", (int8_t*)&systemParams.gateway[2]);
        nvs_get_i8(nvs_handler, "gw4", (int8_t*)&systemParams.gateway[3]);

        nvs_close(nvs_handler);
    }
}

void NVStorage::saveSystemParams(){
    esp_err_t err;
    nvs_handle_t nvs_handler;
    err = nvs_open("storage", NVS_READWRITE, &nvs_handler);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "Saving system params to NVS ...");
        if (systemParams.dhcp == false){
            nvs_set_i8(nvs_handler, "ip1", systemParams.ip[0]);
            nvs_set_i8(nvs_handler, "ip2", systemParams.ip[1]);
            nvs_set_i8(nvs_handler, "ip3", systemParams.ip[2]);
            nvs_set_i8(nvs_handler, "ip4", systemParams.ip[3]);
            nvs_set_i8(nvs_handler, "ma1", systemParams.mask[0]);
            nvs_set_i8(nvs_handler, "ma2", systemParams.mask[1]);
            nvs_set_i8(nvs_handler, "ma3", systemParams.mask[2]);
            nvs_set_i8(nvs_handler, "ma4", systemParams.mask[3]);
            nvs_set_i8(nvs_handler, "gw1", systemParams.gateway[0]);
            nvs_set_i8(nvs_handler, "gw2", systemParams.gateway[1]);
            nvs_set_i8(nvs_handler, "gw3", systemParams.gateway[2]);
            nvs_set_i8(nvs_handler, "gw4", systemParams.gateway[3]);
        }
        nvs_set_i8(nvs_handler, "dhcp", systemParams.dhcp);

        nvs_commit(nvs_handler);
        nvs_close(nvs_handler);
    }
}

void NVStorage::loadESAMotorParams() {
    esp_err_t err;
    nvs_handle_t nvs_handler;
    err = nvs_open("storage", NVS_READWRITE, &nvs_handler);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG,"Reading clutch motor params from NVS ...");
        nvs_get_u32(nvs_handler, "esa_calibrate",        (uint32_t*)&esaParams.calibrate);
        nvs_get_u32(nvs_handler, "esa_inverseEncoder",   (uint32_t*)&esaParams.inverseEncoder);
        nvs_get_u32(nvs_handler, "esa_encoderAngle",     (uint32_t*)&esaParams.encoderAngle);
        nvs_get_u32(nvs_handler, "esa_voltageLimit",     (uint32_t*)&esaParams.voltageLimit);
        nvs_get_u32(nvs_handler, "esa_velLimitHard",     (uint32_t*)&esaParams.velLimitHard);
        nvs_get_u32(nvs_handler, "esa_velProp",          (uint32_t*)&esaParams.velProp);
        nvs_get_u32(nvs_handler, "esa_velIntegral",      (uint32_t*)&esaParams.velIntegral);
        nvs_get_u32(nvs_handler, "esa_velDiff",          (uint32_t*)&esaParams.velDiff);
        nvs_get_u32(nvs_handler, "esa_velRamp",          (uint32_t*)&esaParams.velRamp);
        nvs_get_u32(nvs_handler, "esa_velLimit",         (uint32_t*)&esaParams.velLimit);
        nvs_get_u32(nvs_handler, "esa_velFilter",        (uint32_t*)&esaParams.velFilter);
        nvs_get_u32(nvs_handler, "esa_angleProp",        (uint32_t*)&esaParams.angleProp);
        nvs_get_u32(nvs_handler, "esa_angleLimit",       (uint32_t*)&esaParams.angleLimit);
        nvs_close(nvs_handler);
    }
}

void NVStorage::saveESAMotorParams() {
    esp_err_t err;
    nvs_handle_t nvs_handler;
    err = nvs_open("storage", NVS_READWRITE, &nvs_handler);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        ESP_LOGI(TAG, "Saving clutch motor params to NVS ...");
        nvs_set_i8(nvs_handler, "esa_calibrate",         *(uint8_t*)&esaParams.calibrate);
        nvs_set_i8(nvs_handler, "esa_inverseEncoder",    *(uint8_t*)&esaParams.inverseEncoder);
        nvs_set_u32(nvs_handler, "esa_encoderAngle",     *(uint32_t*)&esaParams.encoderAngle);
        nvs_set_u32(nvs_handler, "esa_voltageLimit",     *(uint32_t*)&esaParams.voltageLimit);
        nvs_set_u32(nvs_handler, "esa_velLimitHard",     *(uint32_t*)&esaParams.velLimitHard);
        nvs_set_u32(nvs_handler, "esa_velProp",          *(uint32_t*)&esaParams.velProp);
        nvs_set_u32(nvs_handler, "esa_velIntegral",      *(uint32_t*)&esaParams.velIntegral);
        nvs_set_u32(nvs_handler, "esa_velDiff",          *(uint32_t*)&esaParams.velDiff);
        nvs_set_u32(nvs_handler, "esa_velRamp",          *(uint32_t*)&esaParams.velRamp);
        nvs_set_u32(nvs_handler, "esa_velLimit",         *(uint32_t*)&esaParams.velLimit);
        nvs_set_u32(nvs_handler, "esa_velFilter",        *(uint32_t*)&esaParams.velFilter);
        nvs_set_u32(nvs_handler, "esa_angleProp",        *(uint32_t*)&esaParams.angleProp);
        nvs_set_u32(nvs_handler, "esa_angleLimit",       *(uint32_t*)&esaParams.angleLimit);
        
        nvs_commit(nvs_handler);
        nvs_close(nvs_handler);
    }
}
