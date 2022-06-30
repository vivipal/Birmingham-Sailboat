#ifndef __TOOLS_H__
#define __TOOLS_H__


#include <Config.h>
#include <math.h>

float sawtooth(const float x);


COORD coord2cart(double lat, double lon);

COORD coord2cart(COORD latlon);


#endif
