#ifndef __WINDSPEED_H__
#define __WINDSPEED_H__


#define WIND_SPEED_PIN 19


class WindSpeed {

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
    float m_wind_speed = 0;
};



#endif
