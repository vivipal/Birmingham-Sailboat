#include "WindSpeed.h"
#include <Arduino.h>


WindSpeed::WindSpeed(){}

WindSpeed::~WindSpeed(){}

void WindSpeed::newRotation(){
  if ((millis() - m_contact_bounce_time) > 15 ) { // debounce the switch contact.
    m_nb_rotations++;
    m_contact_bounce_time = millis();
  }
  if(millis() - m_time_anemometer > 2000){
		m_wind_speed = m_nb_rotations * 1.061/2.0;
		m_nb_rotations = 0;
		m_time_anemometer = millis();
	}
}


void WindSpeed::update(){

  if (millis()-m_time_anemometer > 4000){ // if the sensor hasnt receive any ticks for more than 4s
    m_wind_speed = 0;
      m_nb_rotations = 0;
    m_time_anemometer = millis();
  }
}


float WindSpeed::getSpeed(){
  return m_wind_speed;
}
