

#ifndef __CONFIG_H__
#define __CONFIG_H__



//////  SENSORS CONFIG //////
#define NB_SENSORS 5
enum sensors_name {NAME_IMU, NAME_GPS, NAME_RC, NAME_WDIRECTION, NAME_WSPEED};
/////////////////////////////




////////  RC CONFIG ////////
#define RUDDER_CHANNEL_PIN 3
#define SAIL_CHANNEL_PIN 2
#define CHANNEL_NB 2
enum channel_name {RUDDER_CHANNEL,SAIL_CHANNEL};
#define RUDDER_OFFSETMIN 1140
#define RUDDER_OFFSETMAX 1812
#define SAIL_OFFSETMIN 1076
#define SAIL_OFFSETMAX 1944
/////////////////////////////




//////  SERVOS CONFIG //////
#define NB_SERVOS 2
enum servos_name {NAME_RUDDER, NAME_SAIL};

#define RUDDER_PIN 0
#define RUDDER_PWMMIN 143
#define RUDDER_PWMMAX 428
#define RUDDER_ANGLEMIN -90
#define RUDDER_ANGLEMAX 90

#define SAIL_PIN 1
#define SAIL_PWMMIN 151
#define SAIL_PWMMAX 417
#define SAIL_ANGLEMIN 0
#define SAIL_ANGLEMAX 6*360
/////////////////////////////





///////  CONTROL MODE ///////
enum control_mode {RADIO_CONTROLLED, AUTONOMOUS};
/////////////////////////////






#endif
