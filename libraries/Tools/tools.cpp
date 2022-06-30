#include <tools.h>

float sawtooth(const float x){
  return 2*atan(tan(x/2));
}


COORD coord2cart(double lat, double lon){

  double x_tilde = EARTH_RADIUS * cos(lat*M_PI/180)*(lon-LON_REF)*M_PI/180;
  double y_tilde = EARTH_RADIUS * (lat-LAT_REF)*M_PI/180;

  COORD c;
  c.x = x_tilde;
  c.y = y_tilde;
  return c;
}

COORD coord2cart(COORD latlon){

  double x_tilde = EARTH_RADIUS * cos(latlon.x*M_PI/180)*(latlon.y-LON_REF)*M_PI/180;
  double y_tilde = EARTH_RADIUS * (latlon.x-LAT_REF)*M_PI/180;

  COORD c;
  c.x = x_tilde;
  c.y = y_tilde;
  return c;
}
