#include "DomyroboMotorController.h"
#include "DomyroboSerialComm.h"


#define MOTOR_FLF_PIN   11
#define MOTOR_FLR_PIN   8
#define MOTOR_FLV_PIN   9

#define MOTOR_FRF_PIN   12
#define MOTOR_FRR_PIN   13
#define MOTOR_FRV_PIN   10

#define MOTOR_BLF_PIN   3
#define MOTOR_BLR_PIN   2
#define MOTOR_BLV_PIN   5

#define MOTOR_BRF_PIN   7
#define MOTOR_BRR_PIN   4
#define MOTOR_BRV_PIN   6

#define DOMYROBO_WIDTH  0.1575  // in m
#define WHEEL_RADIUS    0.032   // in m
#define MOTOR_MAX_SPEED 15      // maximum speed at full duty-cycle in rad/s

#define BAUDRATE        115200
#define DELAY_TIME      10




DomyroboSerialComm      serial_comm       = DomyroboSerialComm(BAUDRATE);
DomyroboMotorController motor_controller  = DomyroboMotorController(
  DOMYROBO_WIDTH,
  WHEEL_RADIUS,
  MOTOR_MAX_SPEED,
  MOTOR_FLF_PIN,
  MOTOR_FLR_PIN,
  MOTOR_FLV_PIN, 
  MOTOR_FRF_PIN, 
  MOTOR_FRR_PIN, 
  MOTOR_FRV_PIN, 
  MOTOR_BLF_PIN, 
  MOTOR_BLR_PIN, 
  MOTOR_BLV_PIN, 
  MOTOR_BRF_PIN, 
  MOTOR_BRR_PIN, 
  MOTOR_BRV_PIN
);




void setup() {
  /* Start serial communication */
  serial_comm.begin();

  /* Begin the motor controller */
  motor_controller.begin();
}




void loop() {
  /* Move the motor based on received input */
  serial_comm.readVelInput();
  motor_controller.move(serial_comm.getVelParam());

  /* This delay is mandatory due to Serial communication */
  delay(DELAY_TIME);
}



