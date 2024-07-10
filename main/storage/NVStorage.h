#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

class NVStorage {
private:
    inline static struct system_params_t {
        bool dhcp = true;
        uint8_t ip[4] = {0};
        uint8_t mask[4] = {0};
        uint8_t gateway[4] = {0};
    }
    
    inline static struct esa_motor_params {
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
    };
public:
    static void init();

    static inline system_params_t systemParams;
    static inline esa_motor_params esaParams;

    static void loadSystemParams();
    static void saveSystemParams();

    static void loadESAMotorParams();
    static void saveESAMotorParams();
};