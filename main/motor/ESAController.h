#pragma once

#include "SimpleFOC.h"

class ESAController {
private:
    static inline BLDCMotor wheel_motor = BLDCMotor(1);
    static inline BLDCDriver3PWM wheel_driver = BLDCDriver3PWM(12, 13, 14, 11);
    static inline HallSensor sensor = HallSensor(GPIO_NUM_15, GPIO_NUM_16, GPIO_NUM_17, 1);
public:
    static void init();
    static void motor_timer_callback(void *arg);
};