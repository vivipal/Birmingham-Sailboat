#include "CMPS12.h"


CMPS12::CMPS12(): ss(10,11){

}

void CMPS12::init(){
  ss.begin(9600);
}

CMPS12::~CMPS12(){

}

void CMPS12::update(){
  ss.listen();
  ss.write(CMPS_GET_ANGLE16);  // Request and read 16 bit angle
  while(ss.available() < 2);
  unsigned char high_byte = ss.read();
  unsigned char low_byte = ss.read();
  m_angle16 = high_byte;                // Calculate 16 bit angle
  m_angle16 <<= 8;
  m_angle16 += low_byte;
  m_angle = m_angle16/10 + (float)(m_angle16%10)/10;

  ss.write(CMPS_GET_ANGLE8);  // Request and read 8 bit angle
  while(ss.available() < 1);
  m_angle8 = ss.read();

  ss.write(CMPS_GET_PITCH);   // Request and read pitch value
  while(ss.available() < 1);
  m_pitch = ss.read();

  ss.write(CMPS_GET_ROLL);    // Request and read roll value
  while(ss.available() < 1);
  m_roll = ss.read();

}

double CMPS12::getAngle(){
  return m_angle;
}

double CMPS12::getCos(){
  return cos(m_angle * M_PI/180);
}

double CMPS12::getSin(){
  return sin(m_angle * M_PI/180);
}

float CMPS12::getPitch(){
  return (float)m_pitch;
}
float CMPS12::getRoll(){
  return (float)m_roll;
}
