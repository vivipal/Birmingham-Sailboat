#ifndef __SAILBOAT_H__
#define __SAILBOAT_H__


#include <Config.h>

#include <WindDirection.h>
#include <WindSpeed.h>
#include <CMPS12.h>
#include <GPS.h>
#include <ServoController.h>
#include <RCReceiver.h>
#include <Logger.h>




class Sailboat {

  public:
    Sailboat();

    ~Sailboat();

    void init(Adafruit_PWMServoDriver* servos_pwm);

    WindDirection* wd();
    WindSpeed* ws();
    CMPS12* compass();
    GPS* gps();
    RC* rc();

    Servo_Motor* rudderServo();
    Servo_Motor* sailServo();

    void updateSensors();

    void updateServos();
    int controlMode();



  private:

    Sensor* m_sensor[NB_SENSORS];
    Servo_Motor* m_servo[NB_SERVOS];



};


#endif
