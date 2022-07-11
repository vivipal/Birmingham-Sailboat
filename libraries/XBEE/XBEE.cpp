#include "XBEE.h"




XBEE::XBEE(){}

void XBEE::init(Sailboat* boat){
  XBEE_SERIAL.begin(XBEE_BAUDRATE);
  m_boat = boat;
}


XBEE::~XBEE(){}

void XBEE::update(){
  while (XBEE_SERIAL.available()){
    unsigned char c = XBEE_SERIAL.read();
    if (c==0x6D){receiveMission();}
    else if (c==0x69){sendInfo();}
    else if (c==0x6C){sendInfoLine();}
  }
}


void XBEE::sendInfoLine(){
  COORD_LATLON a = m_boat->getFollowLine()->getPointA();
  COORD_LATLON b = m_boat->getFollowLine()->getPointB();

  XBEE_SERIAL.print(a.lat,8);XBEE_SERIAL.print(";");
  XBEE_SERIAL.print(a.lon,8);XBEE_SERIAL.print(";");
  XBEE_SERIAL.print(b.lat,8);XBEE_SERIAL.print(";");
  XBEE_SERIAL.print(b.lon,8);XBEE_SERIAL.print(";");

  XBEE_SERIAL.print("\n\r");
}


float readFloat(){
  /*
    read the 4 incomming bytes and convert them to float
  */
  float f=0.0;
  uint8_t* b = (uint8_t*) &f;

  while (XBEE_SERIAL.available()<4); // waiting for 4 bytes

  for (size_t i = 0; i < sizeof(f); i++) {
    *(b+i) = (uint8_t)XBEE_SERIAL.read();
  }
  return f;
}

void XBEE::receiveMission(){

  int nb_wp = XBEE_SERIAL.read();

  float lat = 0.0;
  float lon = 0.0;

  for (size_t i = 0; i < nb_wp; i++) {
    lat = readFloat();
    lon = readFloat();
    Serial.print(lat,6);
    Serial.print(" ");
    Serial.println(lon,6);
  }
}

void XBEE::sendInfo(){
  XBEE_SERIAL.print(m_boat->controlMode());XBEE_SERIAL.print(";"); // control mode of the boat

  XBEE_SERIAL.print(m_boat->gps()->getD());XBEE_SERIAL.print(m_boat->gps()->getM());XBEE_SERIAL.print(m_boat->gps()->getY());XBEE_SERIAL.print("-"); // date
  XBEE_SERIAL.print(m_boat->gps()->geth());XBEE_SERIAL.print(m_boat->gps()->getm());XBEE_SERIAL.print(m_boat->gps()->gets());XBEE_SERIAL.print(";"); //time


  XBEE_SERIAL.print(m_boat->wd()->getDirection());XBEE_SERIAL.print(";"); // direction opf the wind
  XBEE_SERIAL.print(m_boat->ws()->getSpeed());XBEE_SERIAL.print(";"); // speed of the wind
  XBEE_SERIAL.print(m_boat->compass()->getAngle());XBEE_SERIAL.print(";"); // heading of the boat
  XBEE_SERIAL.print(m_boat->gps()->getSpeed());XBEE_SERIAL.print(";"); // speed of the boat (gps)

  XBEE_SERIAL.print(m_boat->gps()->getLat(),8);XBEE_SERIAL.print(";"); // latitude
  XBEE_SERIAL.print(m_boat->gps()->getLon(),8);XBEE_SERIAL.print(";"); // longitude

  XBEE_SERIAL.print(m_boat->sailServo()->getLastSet());XBEE_SERIAL.print(";");
  XBEE_SERIAL.print(m_boat->rudderServo()->getLastSet());XBEE_SERIAL.print(";");

  XBEE_SERIAL.print("\n\r");
}
