#ifndef __CMPS12_H__
#define __CMPS12_H__

#include <Sensor.h>
#include <Config.h>

#include <SoftwareSerial.h>
#include <Arduino.h>


class CMPS12: public Sensor {
  public:
    CMPS12();
    void init();
    ~CMPS12();

    void update();
    double getAngle();
    double getCos();
    double getSin();

    float getPitch();
    float getRoll();



  private :
    SoftwareSerial ss;

    double m_angle;
    char m_roll;
    char m_pitch;
    unsigned char m_angle8;
    unsigned int m_angle16;


};





#endif
