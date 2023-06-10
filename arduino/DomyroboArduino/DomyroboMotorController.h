#ifndef _DOMYROBO_MOTOR_CONTROLLER_H_
#define _DOMYROBO_MOTOR_CONTROLLER_H_
#include <Arduino.h>
#include "diff_drive_param.h"




class DomyroboMotorController {


  private:
    uint8_t flf_pin, flr_pin, flv_pin, frf_pin, frr_pin, frv_pin, blf_pin, blr_pin, blv_pin, brf_pin, brr_pin, brv_pin;
    float   width, wheel_radius, max_speed;

    void rightSpeedAdjust(int speed);
    void leftSpeedAdjust(int speed);


  public:
    DomyroboMotorController(float width, float wheel_radius, float max_speed, uint8_t flf_pin, uint8_t flr_pin, uint8_t flv_pin, uint8_t frf_pin, uint8_t frr_pin, uint8_t frv_pin, uint8_t blf_pin, uint8_t blr_pin, uint8_t blv_pin, uint8_t brf_pin, uint8_t brr_pin, uint8_t brv_pin);
    ~DomyroboMotorController();

    void begin();
    void move(diff_drive_param vel);
};




#endif