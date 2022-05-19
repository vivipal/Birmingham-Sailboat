#ifndef __CMPS12_H__
#define __CMPS12_H__


#include <SoftwareSerial.h>
#include <Arduino.h>

#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15

class CMPS12 {
  public:
    CMPS12();
    void init();
    ~CMPS12();

    void update();
    float getAngle();



  private :
    SoftwareSerial ss;
    
    char m_roll;
    char m_pitch;
    unsigned char m_angle8;
    unsigned int m_angle16;


};





#endif
