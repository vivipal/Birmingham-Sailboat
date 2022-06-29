#ifndef __WINDSPEED_H__
#define __WINDSPEED_H__

#include <Sensor.h>
#include <Config.h>
#include <Arduino.h> // millis()



class WindSpeed: public Sensor {

  public:
    WindSpeed();
    ~WindSpeed();

    void newRotation();
    void update();
    float getSpeed();



  private:
    unsigned int m_nb_rotations=0;
    double m_contact_bounce_time=0;
    double m_time_anemometer=0;
    float m_wind_speed=0;
};



#endif
