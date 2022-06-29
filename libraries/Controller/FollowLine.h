#ifndef __FOLLOWLINE_H__
#define __FOLLOWLINE_H__


#include <ControllerInterface.h>
#include <Config.h>
#include <math.h>
#include <Sailboat.h>


class Sailboat;


class FollowLine: public Controller {

  public :
    FollowLine(){};

    void setLine(float lat1,float lon1, float lat2,float lon2, float r=6);

    void updateCmd();

    COORD getPointA();
    COORD getPointB();


  private :

    double m_lat1,m_lon1,m_lat2,m_lon2;
    float m_ax,m_ay,m_bx,m_by, m_r;
    float m_q=1;

};

#endif
