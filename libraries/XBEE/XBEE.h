#ifndef __XBEE_H__
#define __XBEE_H__


#include <Config.h>
#include <Arduino.h>
#include <Sailboat.h>


class Sailboat;

class XBEE {


  public :
    XBEE();
    void init(Sailboat* boat);
    ~XBEE();

    void update();

    void sendInfo();
    void sendInfoLine();
    void receiveMission();
    void controlMode();

  private:
    unsigned int m_last_receive = 0;

    Sailboat* m_boat=NULL;
    unsigned long m_config_start;
};



#endif
