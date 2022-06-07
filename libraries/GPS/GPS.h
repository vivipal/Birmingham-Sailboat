#ifndef __GPS_H__
#define __GPS_H__

#include <Sensor.h>
#include <Config.h>

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <TinyGPS++.h>

#define VALID 1
#define NOT_VALID 0

class GPS: public Sensor {

  public :
    GPS();
    void init();
    ~GPS();

    void update();

    int locationStatus();
    int speedStatus();
    int timeStatus();
    int dateStatus();
    int elevationStatus();

    double getLat();
    double getLon();
    float getSpeed();
    float getElev();
    float geth();
    float getm();
    float gets();
    float getM();
    float getD();
    float getY();

  private:
    SoftwareSerial ss;
    TinyGPSPlus gps;
};


#endif
