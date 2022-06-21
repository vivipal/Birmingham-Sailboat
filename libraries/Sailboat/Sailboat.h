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
#include <XBEE.h>
#include <ControllerInterface.h>


class XBEE;


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
    XBEE* xbee();

    Servo_Motor* rudderServo();
    Servo_Motor* sailServo();

    void updateSensors();

    void updateServos();
    int controlMode();

    void updateTrueWindDirection();
    float getTrueWindDirection(){return m_true_wind_dir;};

    void attachedController(Controller* c){
      if (m_controller){m_controller->disableController();}
      m_controller = c;
      m_controller->enableController();
    }


  private:

    Sensor* m_sensor[NB_SENSORS];
    Servo_Motor* m_servo[NB_SERVOS];

    float m_true_wind_dir=0;

    Controller* m_controller=NULL;


};


#endif
