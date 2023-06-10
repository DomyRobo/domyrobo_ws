#ifndef _DOMYROBO_SERIAL_COMM_H_
#define _DOMYROBO_SERIAL_COMM_H_
#include <Arduino.h>
#include "diff_drive_param.h"




class DomyroboSerialComm {


  private:
    uint32_t          baudrate;
    diff_drive_param  buff_vel;



  public:
    DomyroboSerialComm(uint32_t baudrate);
    ~DomyroboSerialComm();

    void begin();
    void readVelInput();
    float getVelX();
    float getVelOmega();
    diff_drive_param getVelParam();
};





#endif