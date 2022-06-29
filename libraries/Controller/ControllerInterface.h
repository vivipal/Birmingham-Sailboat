#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <Config.h>
#include <Sailboat.h>
class Sailboat;



class Controller {

  public:
    Controller(){};

    init(Sailboat* boat){m_boat=boat;}

    virtual void updateCmd();

    float getRudderCmd() { return m_rudder_setpoint;}
    float getSailCmd() { return m_sail_setpoint;}

    void enableController(){m_enabled=1;}
    void disableController(){m_enabled=0;}
    int status(){return m_enabled;}


  protected:

    Sailboat* m_boat = NULL;

    float m_rudder_setpoint=0.5; // percentage
    float m_sail_setpoint=0.5; // percentage

  private:
    int m_enabled=0;

};
#endif
