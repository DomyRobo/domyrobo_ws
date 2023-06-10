#include "DomyroboSerialComm.h"



DomyroboSerialComm::DomyroboSerialComm(uint32_t baudrate) {
  this->baudrate        = baudrate;
  this->buff_vel.x      = 0.0;
  this->buff_vel.omega  = 0.0; 
}



DomyroboSerialComm::~DomyroboSerialComm() {}



void DomyroboSerialComm::begin() {
  Serial.begin(this->baudrate);
}



void DomyroboSerialComm::readVelInput() {
  if(Serial.available() > 0) {
    /* Obtain a line from serial input and remove the whitespaces */
    String buf = Serial.readStringUntil('\n');
    buf.trim();

    /* Take the number before and after the comma separator */
    uint8_t comma_idx     = buf.indexOf(',');
    this->buff_vel.x      = buf.substring(0, comma_idx).toFloat();
    this->buff_vel.omega  = buf.substring(comma_idx+1).toFloat();
  }
}



float DomyroboSerialComm::getVelX() {
  return this->buff_vel.x;
}



float DomyroboSerialComm::getVelOmega() {
  return this->buff_vel.omega;
}



diff_drive_param DomyroboSerialComm::getVelParam() {
  return this->buff_vel;
}