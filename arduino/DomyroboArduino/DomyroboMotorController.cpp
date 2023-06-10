#include "DomyroboMotorController.h"



DomyroboMotorController::DomyroboMotorController(float width, float wheel_radius, float max_speed, uint8_t flf_pin, uint8_t flr_pin, uint8_t flv_pin, uint8_t frf_pin, uint8_t frr_pin, uint8_t frv_pin, uint8_t blf_pin, uint8_t blr_pin, uint8_t blv_pin, uint8_t brf_pin, uint8_t brr_pin, uint8_t brv_pin) {
  this->width         = width;
  this->wheel_radius  = wheel_radius;
  this->max_speed     = max_speed;
  this->flf_pin       = flf_pin;
  this->flr_pin       = flr_pin;
  this->flv_pin       = flv_pin;
  this->frf_pin       = frf_pin;
  this->frr_pin       = frr_pin;
  this->frv_pin       = frv_pin;
  this->blf_pin       = blf_pin;
  this->blr_pin       = blr_pin;
  this->blv_pin       = blv_pin;
  this->brf_pin       = brf_pin;
  this->brr_pin       = brr_pin;
  this->brv_pin       = brv_pin;
}



DomyroboMotorController::~DomyroboMotorController() {}


void DomyroboMotorController::begin() {
  pinMode(this->flf_pin, OUTPUT);
  pinMode(this->flr_pin, OUTPUT);
  pinMode(this->flv_pin, OUTPUT);
  pinMode(this->frf_pin, OUTPUT);
  pinMode(this->frr_pin, OUTPUT);
  pinMode(this->frv_pin, OUTPUT);
  pinMode(this->blf_pin, OUTPUT);
  pinMode(this->blr_pin, OUTPUT);
  pinMode(this->blv_pin, OUTPUT);
  pinMode(this->brf_pin, OUTPUT);
  pinMode(this->brr_pin, OUTPUT);
  pinMode(this->brv_pin, OUTPUT);
}



void DomyroboMotorController::rightSpeedAdjust(int speed) {
  if(speed < 0) {
    analogWrite(frv_pin, abs(speed));
    analogWrite(brv_pin, abs(speed));
    digitalWrite(frf_pin, LOW);
    digitalWrite(brf_pin, LOW);
    digitalWrite(frr_pin, HIGH);
    digitalWrite(brr_pin, HIGH);
  }
  else {
    analogWrite(frv_pin, abs(speed));
    analogWrite(brv_pin, abs(speed));
    digitalWrite(frf_pin, HIGH);
    digitalWrite(brf_pin, HIGH);
    digitalWrite(frr_pin, LOW);
    digitalWrite(brr_pin, LOW);
  }
}



void DomyroboMotorController::leftSpeedAdjust(int speed) {
  if(speed < 0) {
    analogWrite(flv_pin, abs(speed));
    analogWrite(blv_pin, abs(speed));
    digitalWrite(flf_pin, LOW);
    digitalWrite(blf_pin, LOW);
    digitalWrite(flr_pin, HIGH);
    digitalWrite(blr_pin, HIGH);
  }
  else {
    analogWrite(flv_pin, abs(speed));
    analogWrite(blv_pin, abs(speed));
    digitalWrite(flf_pin, HIGH);
    digitalWrite(blf_pin, HIGH);
    digitalWrite(flr_pin, LOW);
    digitalWrite(blr_pin, LOW);
  }
}



void DomyroboMotorController::move(diff_drive_param vel) {
  /* Get the value in rad/s */
  float right_speed = (2.0*vel.x + this->width*vel.omega)/(2.0*this->wheel_radius),
        left_speed  = (2.0*vel.x - this->width*vel.omega)/(2.0*this->wheel_radius);

  /* Map to 0 - 255 */
  int r_speed = (fabs(right_speed) >= this->max_speed) ? ((right_speed < 0) ? -255 : 255) : (int)((right_speed/this->max_speed)*255.0),
      l_speed = (fabs(left_speed) >= this->max_speed)  ? ((left_speed < 0) ? -255 : 255)  : (int)((left_speed/this->max_speed)*255.0);
      
  /* Move the motor */
  rightSpeedAdjust(r_speed);
  leftSpeedAdjust(l_speed);
}