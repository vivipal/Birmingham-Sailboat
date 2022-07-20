#ifndef __XBEE_H__
#define __XBEE_H__


#include <Config.h>
#include <Arduino.h>
#include <Sailboat.h>
#include <Logger.h>


class Sailboat;

class XBEE {


  public :
    XBEE();
    void init(Sailboat* boat, Logger* logger);
    ~XBEE();

    void update();

    void sendInfo();
    void sendInfoLine();
    void receiveMission();
    void controlMode();
    void logger();


  private:
    unsigned int m_last_receive = 0;

    Sailboat* m_boat=NULL;
    unsigned long m_config_start;
    Logger* m_logger=NULL;
};



#endif
