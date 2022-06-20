#ifndef __XBEE_H__
#define __XBEE_H__


#include <Sensor.h>
#include <Config.h>
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Sailboat.h>


class Sailboat;

class XBEE : public Sensor{


  public :
    XBEE();
    void init();
    ~XBEE();

    void update();
    int isReceiving();
    const SoftwareSerial& serial(){return ss;}



  private:
    SoftwareSerial ss;
    unsigned int m_last_receive = 0;


};



#endif
