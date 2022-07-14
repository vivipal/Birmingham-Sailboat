#include <Controllers.h>


void FollowLine::setLine(float lat1,float lon1, float lat2,float lon2, float r=6){
  m_lat1 = lat1;
  m_lon1 = lon1;
  m_lat2 = lat2;
  m_lon2 = lon2;

  COORD_XY a = coord2cart(lat1,lon1);
  COORD_XY b = coord2cart(lat2,lon2);

  m_ax = a.x;
  m_ay = a.y;
  m_bx = b.x;
  m_by = b.y;
  m_r = r;

  m_status = 1;
};

void FollowLine::setLine(COORD_LATLON a, COORD_LATLON b, float r=6){
  setLine(a.lat,a.lon,b.lat,b.lon,r);
}


void FollowLine::updateCmd(){
  COORD_XY m = m_boat->gps()->getXY();

  float x = m.x;
  float y = m.y;

  float theta = ((int)(-1*m_boat->compass()->getAngle()+90)%360)*M_PI/180;
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

  m_rudder_setpoint = 1-(deltar+DELTARMAX)/(2*DELTARMAX);
  m_sail_setpoint = (deltasmax)/(ANGLE_SAILMAX*M_PI/180);
};



COORD_LATLON FollowLine::getPointA(){
  COORD_LATLON c;
  c.lat = m_lat1;
  c.lon = m_lon1;
  return c;
}

COORD_LATLON FollowLine::getPointB(){
  COORD_LATLON c;
  c.lat = m_lat2;
  c.lon = m_lon2;
  return c;
}

NoneController::NoneController(){
  m_status=1;
}

void NoneController::updateCmd(){
  m_rudder_setpoint = 0.5;
  m_sail_setpoint = 1;
}
