#include "XBEE.h"




XBEE::XBEE(){}

void XBEE::init(Sailboat* boat){
  XBEE_SERIAL.begin(XBEE_BAUDRATE);
  m_boat = boat;
}


XBEE::~XBEE(){}

void XBEE::update(){
  while (XBEE_SERIAL.available()){
    char c = Serial.read();
    if (c=0x63){enterConfigMode();}
  }
}


void XBEE::enterConfigMode(){ // just test for the moment
  m_config_start = millis();
  while (1){

    if (XBEE_SERIAL.available()){
      m_config_start = millis();
      char c = XBEE_SERIAL.read();
      switch (c){
        case 0x67: // 'g'
          while(XBEE_SERIAL.available()<10){
            XBEE_SERIAL.println(XBEE_SERIAL.available());
          }
          XBEE_SERIAL.println("G");

          break;
        case 0x77: // 'w'
          XBEE_SERIAL.println("W");

          break;

      }
    }

    if ((millis()-m_config_start)>5000){break;}
  }
}
