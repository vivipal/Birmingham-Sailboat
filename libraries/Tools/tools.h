#ifndef __TOOLS_H__
#define __TOOLS_H__


#include <Config.h>
#include <math.h>

float sawtooth(const float x);


COORD_XY coord2cart(double lat, double lon);

COORD_XY coord2cart(COORD_LATLON latlon);


#endif
