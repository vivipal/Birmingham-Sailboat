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
float GPS::getCourse(){return courseStatus() ? gps.course.deg() : -1;}
float GPS::getElev(){return elevationStatus() ? gps.altitude.meters() : 99999;}

int GPS::getTime(){return timeStatus() ? gps.time.value() : 0;}
int GPS::geth(){return timeStatus() ? gps.time.hour() : -1;}
int GPS::getm(){return timeStatus() ? gps.time.minute() : -1;}
int GPS::gets(){return timeStatus() ? gps.time.second() : -1;}

int GPS::getDate(){return dateStatus() ? gps.date.value() : 0;}
int GPS::getM(){return dateStatus() ? gps.date.month() : -1;}
int GPS::getD(){return dateStatus() ? gps.date.day() : -1;}
int GPS::getY(){return dateStatus() ? gps.date.year() : -1;}

int GPS::locationStatus(){
  return gps.location.isValid() ? VALID : NOT_VALID;
}

int GPS::speedStatus(){
  return gps.speed.isValid() ? VALID : NOT_VALID;
}

int GPS::courseStatus(){
  return gps.course.isValid() ? VALID : NOT_VALID;
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

COORD GPS::getXY(float lat_0=52.489471, float lon_0=-1.898575){

  float lat = gps.location.lat();
  float lon = gps.location.lng();

  float x_tilde = EARTH_RADIUS * cos(lat*M_PI/180)*(lon-lon_0)*M_PI/180;
  float y_tilde = EARTH_RADIUS * (lat-lat_0)*M_PI/180;

  COORD c;
  c.x = x_tilde;
  c.y = y_tilde;
  return c;
}
