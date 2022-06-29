#include <FollowLine.h>


void FollowLine::setLine(float lat1,float lon1, float lat2,float lon2, float r=6){
  m_lat1 = lat1;
  m_lon1 = lon1;
  m_lat2 = lat2;
  m_lon2 = lon2;

  COORD a = coord2cart(lat1,lon1);
  COORD b = coord2cart(lat2,lon2);

  m_ax = a.x;
  m_ay = a.y;
  m_bx = b.x;
  m_by = b.y;
  m_r = r;
};

void FollowLine::updateCmd(){
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

  m_rudder_setpoint = (deltar+DELTARMAX)/(2*DELTARMAX);
  m_sail_setpoint = (deltasmax)/(ANGLE_SAILMAX*M_PI/180);
};



COORD FollowLine::getPointA(){
  COORD c;
  c.x = m_lat1;
  c.y = m_lon1;
  return c;
}

COORD FollowLine::getPointB(){
  COORD c;
  c.x = m_lat2;
  c.y = m_lon2;
  return c;
}
