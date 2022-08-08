#include "RCReceiver.h"



RC::RC(){
  m_offsetmin[RUDDER_CHANNEL] = RUDDER_OFFSETMIN;
  m_offsetmax[RUDDER_CHANNEL] = RUDDER_OFFSETMAX;
  m_offsetmin[SAIL_CHANNEL] = SAIL_OFFSETMIN;
  m_offsetmax[SAIL_CHANNEL] = SAIL_OFFSETMAX;

  m_filtered_value[RUDDER_CHANNEL]=0;
  m_filtered_value[SAIL_CHANNEL]=0;
  m_raw_value[RUDDER_CHANNEL]=0;
  m_raw_value[SAIL_CHANNEL]=0;

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

    m_raw_value[channel] = received_pwm;
    m_filtered_value[channel] = received_filtered;
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
