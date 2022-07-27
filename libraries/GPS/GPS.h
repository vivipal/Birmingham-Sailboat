#ifndef __GPS_H__
#define __GPS_H__

#include <Sensor.h>
#include <Config.h>
#include <tools.h>

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

    COORD_LATLON getLatLon();
    COORD_XY getXY();
  private:
    TinyGPSPlus gps;
};


#endif
