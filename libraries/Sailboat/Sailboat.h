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
    Sailboat() {
      m_sensor[NAME_IMU] =  new CMPS12();
      m_sensor[NAME_GPS] = new GPS();
      m_sensor[NAME_RC] = new RC();
      m_sensor[NAME_WDIRECTION] = new WindDirection();
      m_sensor[NAME_WSPEED] = new WindSpeed();

      m_servo[NAME_RUDDER] = new Servo_Motor(RUDDER_PIN, RUDDER_PWMMIN, RUDDER_PWMMAX, RUDDER_ANGLEMIN, RUDDER_ANGLEMAX);
      m_servo[NAME_SAIL] = new Servo_Motor(SAIL_PIN, SAIL_PWMMIN, SAIL_PWMMAX, SAIL_ANGLEMIN, SAIL_ANGLEMAX);
    };

    ~Sailboat() {
      for (size_t i = 0; i < NB_SENSORS; i++) {
        delete m_sensor[i];
      }
    }

    void init(Adafruit_PWMServoDriver* servos_pwm){
      for (size_t i = 0; i < NB_SENSORS; i++) {
        m_sensor[i]->init();
      }

      for (size_t i = 0; i < NB_SERVOS; i++) {
        m_servo[i]->init(servos_pwm);
      }
    }

    WindDirection* wd(){return (WindDirection*) m_sensor[NAME_WDIRECTION];};
    WindSpeed* ws(){return (WindSpeed*) m_sensor[NAME_WSPEED];};
    CMPS12* compass(){return (CMPS12*) m_sensor[NAME_IMU];};
    GPS* gps(){return (GPS*) m_sensor[NAME_GPS];};
    RC* rc(){return (RC*) m_sensor[NAME_RC];};

    Servo_Motor* rudderServo(){return (Servo_Motor*) m_servo[NAME_RUDDER];};
    Servo_Motor* sailServo(){return (Servo_Motor*) m_servo[NAME_SAIL];};

    void updateSensors(){
      for (size_t i = 0; i < NB_SENSORS; i++) {
        m_sensor[i]->update();
      }
    }

    void updateServos(){
        m_servo[NAME_SAIL]->set( rc()->getValue(SAIL_CHANNEL) );
        m_servo[NAME_RUDDER]->set( rc()->getValue(RUDDER_CHANNEL) );
    }

    int controlMode(){return rc()->isReceiving() ? RADIO_CONTROLLED : AUTONOMOUS;}



  private:

    Sensor* m_sensor[NB_SENSORS];
    Servo_Motor* m_servo[NB_SERVOS];



};


#endif
