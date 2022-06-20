#include "XBEE.h"


XBEE::XBEE() : ss(XBEE_PIN_RX,XBEE_PIN_TX){}

void XBEE::init(){
  ss.begin(XBEE_BAUDRATE);
}

XBEE::~XBEE(){}

void XBEE::update(){
  ss.listen();
  if (ss.available()){
    while (ss.available() > 0){
      ss.read();
    }
    m_last_receive = millis();
  }
}


int XBEE::isReceiving(){
  return ss.available()||((millis-m_last_receive)<500);
}
