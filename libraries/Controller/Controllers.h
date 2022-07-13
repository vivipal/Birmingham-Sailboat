#ifndef __CONTROLLERS_H__
#define __CONTROLLERS_H__


#include <ControllerInterface.h>
#include <Config.h>
#include <math.h>
#include <Sailboat.h>


class Sailboat;

class FollowLine: public Controller {
  public :
    FollowLine(){};

    void setLine(float lat1,float lon1, float lat2,float lon2, float r=6);
    void setLine(COORD_LATLON a, COORD_LATLON b, float r=6);

    void updateCmd();

    COORD_LATLON getPointA();
    COORD_LATLON getPointB();

  private :
    double m_lat1=0.0,m_lon1=0.0,m_lat2=0.0,m_lon2=0.0;
    float m_ax=0.0,m_ay=0.0,m_bx=0.0,m_by=0.0, m_r=6;
    float m_q=1;
};

class NoneController: public Controller {
  public :
    NoneController();
    void updateCmd();
};

#endif
