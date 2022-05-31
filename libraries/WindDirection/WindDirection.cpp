#include "WindDirection.h"
#include <Arduino.h>

WindDirection::WindDirection(){}

WindDirection::~WindDirection(){}


void WindDirection::init(){

  pinMode(WIND_DIRECTION_PIN,INPUT);
}


void WindDirection::update(){

  float value = analogRead(WIND_DIRECTION_PIN);

  m_raw = value;
  m_direction =  map(value, WIND_DIRECTION_SENSOR_MIN, WIND_DIRECTION_SENSOR_MAX, 0, 360); // angle between 0 and 360 degrees
}

float WindDirection::getRawValue(){
  return m_raw;
}

int WindDirection::getDirection(){
  return m_direction;
}

double WindDirection::getCos(){
  return cos(m_direction * M_PI/180);
}

double WindDirection::getSin(){
  return sin(m_direction * M_PI/180);
}
