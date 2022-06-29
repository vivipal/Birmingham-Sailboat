#ifndef __WINDDIRECTION__H__
#define __WINDDIRECTION__H__

#include <Sensor.h>
#include <Config.h>
#include <Arduino.h>


class WindDirection: public Sensor {

  public :
    WindDirection();
    void init();
    ~WindDirection();

    void update();
    float getRawValue();
    int getDirection();
    double getCos();
    double getSin();




  private :
    float m_raw;
    float m_direction = 0;
};


#endif
