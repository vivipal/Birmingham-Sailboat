#ifndef __GPS_H__
#define __GPS_H__

#include <Sensor.h>
#include <Config.h>

#include <SoftwareSerial.h>
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
    int courseStatus();
    int timeStatus();
    int dateStatus();
    int elevationStatus();

    double getLat();
    double getLon();
    float getSpeed();
    float getCourse();
    float getElev();

    int geth();
    int getm();
    int gets();
    int getM();
    int getD();
    int getY();

    COORD getXY(double lat_0=52.489471, double lon_0=-1.898575);
  private:
    SoftwareSerial ss;
    TinyGPSPlus gps;
};


#endif
