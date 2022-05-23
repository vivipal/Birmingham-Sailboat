#include "ServoController.h"


Servo_Motor::Servo_Motor(uint8_t pin, unsigned int pwmMin, unsigned int pwmMax, float anglemin, float anglemax)
:m_pin(pin), m_pwmMin(pwmMin),m_pwmMax(pwmMax),m_anglemin(anglemin), m_anglemax(anglemax){
  m_pwmMid = (int)((pwmMin+pwmMax)/2);
};


void Servo_Motor::init(Adafruit_PWMServoDriver* motor_ptr){
  m_motor = motor_ptr;

  m_motor->begin();
  m_motor->setPWMFreq(50);
  m_motor-> setPWM(m_pin,0,m_pwmMid);
}


void Servo_Motor::setPWM(unsigned int pulse){
  m_motor-> setPWM(m_pin,0,pulse);
}

float Servo_Motor::minPWM(){
  return m_pwmMin;
}
float Servo_Motor::maxPWM(){
  return m_pwmMax;
}
