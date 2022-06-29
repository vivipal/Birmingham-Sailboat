#ifndef __RCRECEIVER_H__
#define __RCRECEIVER_H__

#include <Sensor.h>
#include <Config.h>
#include <Arduino.h> // millis() & micros() & digitalRead()

class RC: public Sensor{
  public :

    RC();


    void interruptCH(int pin, int channel);

    float getRawValue(int channel);
    float getFilteredValue(int channel);
    float getValue(int channel);

    int isReceiving();


  private :
    unsigned long m_start_time[CHANNEL_NB];
    unsigned long m_raw_value[CHANNEL_NB];
    unsigned long m_filtered_value[CHANNEL_NB];
    float m_value[CHANNEL_NB];

    unsigned long m_offsetmax[CHANNEL_NB];
    unsigned long m_offsetmin[CHANNEL_NB];

    unsigned long m_last_interrupt;

};



#endif
