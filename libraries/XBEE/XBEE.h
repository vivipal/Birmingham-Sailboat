#ifndef __XBEE_H__
#define __XBEE_H__


#include <Sensor.h>
#include <Config.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

class XBEE : public Sensor{


  public :
    XBEE();
    void init();
    ~XBEE();

    void update();
    int isReceiving();



  private:
    SoftwareSerial ss;
    unsigned int m_last_receive = 0;


};



#endif
