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
    double m_lat1,m_lon1,m_lat2,m_lon2;
    float m_ax,m_ay,m_bx,m_by, m_r;
    float m_q=1;
};

class NoneController: public Controller {
  public :
    NoneController();
    void updateCmd();
};

#endif
