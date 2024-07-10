#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

class NVStorage {
public:
    static void init();

    static inline struct system_params_t {
        bool dhcp = true;
        uint8_t ip[4] = {0};
        uint8_t mask[4] = {0};
        uint8_t gateway[4] = {0};
    } systemParams {
        .dhcp = true,
        .ip = {0},
        .mask = {0},
        .gateway = {0}
    };

    static inline struct esa_motor_params {
        bool calibrate = true;
        bool inverseEncoder = false;
        float encoderAngle = 3.14;
        float voltageLimit = 6;
        float velLimitHard = 999;
        float velProp = 1;
        float velIntegral = 25;
        float velDiff = 0.003;
        float velRamp = 1000;
        float velLimit = 7;
        float velFilter = 0.002;
        float angleProp = 47;
        float angleLimit = 100;
    } esaParams {
        .calibrate = true,
        .inverseEncoder = false,
        .encoderAngle = 3.14,
        .voltageLimit = 6,
        .velLimitHard = 999,
        .velProp = 1,
        .velIntegral = 25,
        .velDiff = 0.003,
        .velRamp = 1000,
        .velLimit = 7,
        .velFilter = 0.002,
        .angleProp = 47,
        .angleLimit = 100
    };

    static void loadSystemParams();
    static void saveSystemParams();

    static void loadESAMotorParams();
    static void saveESAMotorParams();
};