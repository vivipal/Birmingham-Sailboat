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

    int status(){return m_status;} // 0 if controller not ready/set


  protected:

    Sailboat* m_boat = NULL;

    float m_rudder_setpoint=0.5; // percentage
    float m_sail_setpoint=0.5; // percentage

  private:
    int m_status=0;

};
#endif
