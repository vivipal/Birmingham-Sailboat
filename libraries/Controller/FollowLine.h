#ifndef __FOLLOWLINE_H__
#define __FOLLOWLINE_H__


#include <ControllerInterface.h>
#include <Config.h>

float sawtooth(const float x){
  return 2*atan(tan(x/2));
}

class FollowLine: public Controller {

  public :

    FollowLine(Sailboat *boat): Controller{boat}{};

    void setLine(float ax,float ay, float bx,float by, float r=6){
      m_ax = ax;
      m_ay = ay;
      m_bx = bx;
      m_by = by;
      m_r = r;
    };



    void updateCmd(){
      COORD m = m_boat->gps()->getXY();

      float x = m.x;
      float y = m.y;

      float theta = m_boat->compass()->getAngle();
      float psi = m_boat->getTrueWindDirection();

      float dx = m_bx-m_ax;
      float dy = m_by-m_ay;

      float N = pow(pow(dx,2) + pow(dy,2),.5);
      float e = dx/N *(y-m_ay)  -  dy/N *(x-m_ax);
      if (abs(e) > m_r){
        m_q = e*abs(e);
      }
      float phi = atan2(dy,dx);
      float theta_bar = phi - atan(e/m_r);
      if ((cos(psi-theta_bar) + cos(ZETA) < 0) || ((abs(e)-m_r<0) && (cos(psi-phi)+cos(ZETA)<0))){
        theta_bar = M_PI + psi -m_q*ZETA;
      }
      float deltar = DELTARMAX / M_PI * sawtooth(theta-theta_bar);
      float deltasmax = M_PI/2 * pow((cos(psi-theta_bar)+1)/2,log(M_PI/2/BETA)/log(2));

      m_rudder_setpoint = (m_deltar+DELTARMAX)/(2*DELTARMAX);
      m_sail_setpoint = (m_deltasmax)/(ANGLE_SAILMAX*M_PI/180);
    };




  private :

    float m_ax,m_ay,m_bx,m_by, m_r;
    float m_q=1;

};



#endif
