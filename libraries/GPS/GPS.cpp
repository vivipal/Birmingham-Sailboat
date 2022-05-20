#include "GPS.h"



GPS::GPS() : ss(12,13){}

void GPS::init(){
  ss.begin(9600);
}

GPS::~GPS(){}

void GPS::update(){
  ss.listen();
  while (ss.available() > 0){
    gps.encode(ss.read());
  }
}

double GPS::getLat(){
  return status() ? gps.location.lat() : 0.;
}
double GPS::getLon(){
  return status() ? gps.location.lng() : 0.;
}

int GPS::status(){
  return gps.location.isValid() ? GPS_VALID : GPS_NOT_VALID;
}
