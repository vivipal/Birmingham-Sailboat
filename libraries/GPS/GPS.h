#ifndef __GPS_H__
#define __GPS_H__

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <TinyGPS++.h>

#define GPS_VALID 1
#define GPS_NOT_VALID 0

class GPS {

  public :
    GPS();
    void init();
    ~GPS();

    void update();

    double getLat();
    double getLon();
    int status();

  private:
    SoftwareSerial ss;
    TinyGPSPlus gps;
};


#endif
