#include "RCReceiver.h"

#include <Arduino.h>


RC::RC(){
  m_offsetmin[0] = 1140;
  m_offsetmax[0] = 1812;
  m_offsetmin[1] = 1076;
  m_offsetmax[1] = 1944;
  m_filtered_value[0]=0;
  m_filtered_value[1]=0;
  m_raw_value[0]=0;
  m_raw_value[1]=0;

  m_last_interrupt = 0;

}

void RC::interruptCH(int pin, int channel){
  m_last_interrupt = millis();
  if (digitalRead(pin) == HIGH){
    m_start_time[channel] = micros();
  }else{
    unsigned long received_pwm = micros() - m_start_time[channel];
    float alpha = 0.95;
    unsigned long received_filtered = alpha*m_filtered_value[channel] + (1-alpha)*received_pwm;

    if ((m_offsetmin[channel]<received_pwm && received_pwm<m_offsetmax[channel]) && (abs((int)received_pwm-(int)m_raw_value[channel])< 200||m_raw_value[channel]==0)){
      m_raw_value[channel] = received_pwm;
      m_filtered_value[channel] = received_filtered;
    }
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
  return ((float)m_filtered_value[channel]-(float)m_offsetmin[channel])/((float)m_offsetmax[channel]-(float)m_offsetmin[channel]);
}
