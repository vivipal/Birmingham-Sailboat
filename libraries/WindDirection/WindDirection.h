#ifndef __WINDDIRECTION__H__
#define __WINDDIRECTION__H__


#define WIND_DIRECTION_PIN A14
#define WIND_DIRECTION_SENSOR_MIN 0
#define WIND_DIRECTION_SENSOR_MAX 1023


class WindDirection {

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
