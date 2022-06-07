#include "GPS.h"



GPS::GPS() : ss(GPS_PIN_RX,GPS_PIN_TX){}

void GPS::init(){
  ss.begin(GPS_BAUDRATE);
}

GPS::~GPS(){}

void GPS::update(){
  ss.listen();
  while (ss.available() > 0){
    gps.encode(ss.read());
  }
}

double GPS::getLat(){return locationStatus() ? gps.location.lat() : 99999;}
double GPS::getLon(){return locationStatus() ? gps.location.lng() : 99999;}

float GPS::getSpeed(){return speedStatus() ? gps.speed.kmph() : -1;}
float GPS::getElev(){return elevationStatus() ? gps.altitude.meters() : 99999;}

float GPS::geth(){return timeStatus() ? gps.time.hour() : -1;}
float GPS::getm(){return timeStatus() ? gps.time.minute() : -1;}
float GPS::gets(){return timeStatus() ? gps.time.second() : -1;}

float GPS::getM(){return timeStatus() ? gps.date.month() : -1;}
float GPS::getD(){return timeStatus() ? gps.date.day() : -1;}
float GPS::getY(){return timeStatus() ? gps.date.year() : -1;}

int GPS::locationStatus(){
  return gps.location.isValid() ? VALID : NOT_VALID;
}

int GPS::speedStatus(){
  return gps.speed.isValid() ? VALID : NOT_VALID;
}

int GPS::timeStatus(){
  return gps.time.isValid() ? VALID : NOT_VALID;
}

int GPS::dateStatus(){
  return gps.date.isValid() ? VALID : NOT_VALID;
}

int GPS::elevationStatus(){
  return gps.altitude.isValid() ? VALID : NOT_VALID;
}
