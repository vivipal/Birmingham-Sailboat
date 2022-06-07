#ifndef __SAILBOAT_H__
#define __SAILBOAT_H__


#include <WindDirection.h>
#include <WindSpeed.h>
#include <CMPS12.h>
#include <GPS.h>
#include <ServoController.h>
#include <RCReceiver.h>
#include <Logger.h>


#define NB_SENSORS 5
enum sensors_name {
  NAME_IMU,
  NAME_GPS,
  NAME_RC,
  NAME_WDIRECTION,
  NAME_WSPEED
};

class Sailboat {
  public:


    Sailboat() {
      m_sensor[NAME_IMU] =  new CMPS12();
      m_sensor[NAME_GPS] = new GPS();
      m_sensor[NAME_RC] = new RC();
      m_sensor[NAME_WDIRECTION] = new WindDirection();
      m_sensor[NAME_WSPEED] = new WindSpeed();
    };

    ~Sailboat() {
      for (size_t i = 0; i < NB_SENSORS; i++) {
        delete m_sensor[i];
      }
    }

    void init(){
      for (size_t i = 0; i < NB_SENSORS; i++) {
        m_sensor[i]->init();
      }
    }

    WindDirection* wd(){return (WindDirection*) m_sensor[NAME_WDIRECTION];};
    WindSpeed* ws(){return (WindSpeed*) m_sensor[NAME_WSPEED];};
    CMPS12* compass(){return (CMPS12*) m_sensor[NAME_IMU];};
    GPS* gps(){return (GPS*) m_sensor[NAME_GPS];};
    RC* rc(){return (RC*) m_sensor[NAME_RC];};

    void updateSensors(){
      for (size_t i = 0; i < NB_SENSORS; i++) {
        m_sensor[i]->update();
      }
    }



  private:

    Sensor* m_sensor[NB_SENSORS];



};


#endif
