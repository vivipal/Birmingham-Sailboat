#ifndef __SERVOCONTROLLER_H__
#define __SERVOCONTROLLER_H__


#include <Adafruit_PWMServoDriver.h>

class Servo_Motor {
  public:
    Servo_Motor(uint8_t pin, unsigned int pwmMin, unsigned int pwmMax, float anglemin, float anglemax);
    void init(Adafruit_PWMServoDriver* motor_ptr);

    void setPWM(unsigned int pulse);
    void set(float percent);
    float getLastSet();
    float minPWM();
    float maxPWM();



  private:

    Adafruit_PWMServoDriver* m_motor;


    uint8_t m_pin;
    unsigned int m_pwmMin;
    unsigned int m_pwmMid;
    unsigned int m_pwmMax;
    float m_anglemin;
    float m_anglemax;

    float m_last_set=-1;



};



#endif
