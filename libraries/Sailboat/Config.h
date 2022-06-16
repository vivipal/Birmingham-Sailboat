

#ifndef __CONFIG_H__
#define __CONFIG_H__


#define EARTH_RADIUS 6372800 // Earth radius in meter

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

///////  GPS CONFIG  ///////
#define GPS_PIN_RX 12
#define GPS_PIN_TX 13
#define GPS_BAUDRATE 9600

struct COORD {
  double x = 0;
  double y = 0;
};
/////////////////////////////


///////  CMPS CONFIG  ///////
#define CMPS_PIN_RX 10
#define CMPS_PIN_TX 11
#define CMPS_BAUDRATE 9600


#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15

////////////////////////////

/////////  SD CONFIG /////////
#define PIN_SD_CARD 53 // SS pin  (50 (MISO), 51 (MOSI), 52 (SCK))
/////////////////////////////



/////////  W DIR CONFIG /////////
#define WIND_DIRECTION_PIN A14
#define WIND_DIRECTION_SENSOR_MIN 0
#define WIND_DIRECTION_SENSOR_MAX 1023
////////////////////////////////



/////////  W DIR CONFIG /////////
#define WIND_SPEED_PIN 19
////////////////////////////////


//////////  LOG CONFIG //////////
#define LOG_PERIOD 500 // milliseconds
////////////////////////////////


#endif
