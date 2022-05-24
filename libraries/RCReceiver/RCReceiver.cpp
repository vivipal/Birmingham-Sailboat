#include "RCReceiver.h"

#include <Arduino.h>

RC::RC(){
  m_offsetmin[0] = 1140;
  m_offsetmax[0] = 1812;
  m_offsetmin[1] = 1076;
  m_offsetmax[1] = 1936;
  m_filtered_value[0]=0;
  m_filtered_value[1]=0;

  m_last_interrupt = 0;

}

void RC::interruptCH(int pin, int channel){
  m_last_interrupt = millis();
  if (digitalRead(pin) == HIGH){
    m_start_time[channel] = micros();
  }else{
    m_filtered_value[channel] = m_filtered_value[channel]*0.99 + 0.01*(micros() - m_start_time[channel]);
    m_raw_value[channel] = micros() - m_start_time[channel];
  }
}

int RC::isReceiving(){
  return (millis()-m_last_interrupt)>100 ? 0 : 1;
}


float RC::getRawValue(int channel){
  return m_raw_value[channel];
}

float RC::getFilteredValue(int channel){
  return m_filtered_value[channel];
}

float RC::getValue(int channel){
  return (m_raw_value[channel]-m_offsetmin[channel])/(m_offsetmax[channel]-m_offsetmin[channel]);
}
