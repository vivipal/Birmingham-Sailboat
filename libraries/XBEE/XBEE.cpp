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
    if (c==0x63){enterConfigMode();}
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


void XBEE::enterConfigMode(){ // just test for the moment
  m_config_start = millis();
  XBEE_SERIAL.println("Enter config mode.");
  while (1){

    if (XBEE_SERIAL.available()){
      m_config_start = millis();
      unsigned char c = XBEE_SERIAL.read();
      switch (c){
        case 0x67: // 'g'
          XBEE_SERIAL.println("G");

          break;
        case 0x77: // 'w'
          XBEE_SERIAL.println("W");

          break;

      }
    }
    if ((millis()-m_config_start)>5000){break;}
  }
  XBEE_SERIAL.println("Exit config mode.");
}
