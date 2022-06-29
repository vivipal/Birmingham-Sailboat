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

    void setLine(float ax,float ay, float bx,float by, float r=6);

    void updateCmd();


  private :

    float m_ax,m_ay,m_bx,m_by, m_r;
    float m_q=1;

};

#endif
