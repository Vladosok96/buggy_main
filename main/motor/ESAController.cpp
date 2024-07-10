#include "ESAController.h"

#include "esp_timer.h"

void ESAController::init() {
    sensor.init();
    sensor.pullup = Pullup::USE_INTERN;

    wheel_motor.linkSensor(&sensor);
    wheel_driver.voltage_power_supply = 12;
    wheel_driver.pwm_frequency = 20000;
    wheel_driver.init();
    wheel_motor.linkDriver(&wheel_driver);
    wheel_motor.voltage_limit = 5;
    wheel_motor.controller = MotionControlType::torque;
    wheel_motor.foc_modulation = FOCModulationType::SpaceVectorPWM;
    wheel_motor.init();

    wheel_motor.initFOC(4.61, Direction::CW);
    wheel_motor.initFOC();

    const esp_timer_create_args_t motors_timer_args = {
        .callback = &ESAController::motor_timer_callback,
        .name = "motor_timer"};

    esp_timer_handle_t motors_timer;
    ESP_ERROR_CHECK(esp_timer_create(&motors_timer_args, &motors_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(motors_timer, 500));

    wheel_motor.enable();
    wheel_motor.target = 0;
}

void ESAController::motor_timer_callback(void *arg) {
    int64_t timer = esp_timer_get_time();
    sensor.handleAll();
    wheel_motor.loopFOC();
    wheel_motor.move();
    timer = esp_timer_get_time() - timer;
}