#include "XBEE.h"




XBEE::XBEE(){}

void XBEE::init(Sailboat* boat, Logger* logger){
  XBEE_SERIAL.begin(XBEE_BAUDRATE);
  m_boat = boat;

  m_logger = logger;
}


XBEE::~XBEE(){}

void XBEE::update(){
  while (XBEE_SERIAL.available()){
    unsigned char c = XBEE_SERIAL.read();
    if (c==0x6D){receiveMission();}
    else if (c==0x69){sendInfo();}
    else if (c==0x6C){sendInfoLine();}
    else if (c==0x63){controlMode();}
    else if (c==0x73){logger();}
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

  while (XBEE_SERIAL.available()<1);

  int nb_wp = XBEE_SERIAL.read();

  float lat = 0.0;
  float lon = 0.0;

  m_boat->getMP()->reset();
  COORD_LATLON tmp;
  for (size_t i = 0; i < nb_wp; i++) {
    tmp.lat = readFloat();
    tmp.lon = readFloat();
    m_boat->getMP()->setWP(i+1,tmp);
  }
  m_boat->getMP()->start();
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

  XBEE_SERIAL.print(m_boat->getTrueWindDirection());XBEE_SERIAL.print(";");
  XBEE_SERIAL.print(m_boat->getMP()->nb_wp_passed());XBEE_SERIAL.print(";");
  XBEE_SERIAL.print("\n\r");
}


void XBEE::controlMode(){

  char c = 'a'; // useless caracter
  float rudder_setpoint  = m_boat->rudderServo()->getLastSet();
  float sail_setpoint = m_boat->sailServo()->getLastSet();
  while(c!=0x71) {
    while(!XBEE_SERIAL.available());
    c = XBEE_SERIAL.read();
    switch (c) {
      case 0x68:
        rudder_setpoint+=0.05;
        if (rudder_setpoint>1){rudder_setpoint=1;}
        m_boat->rudderServo()->set(rudder_setpoint);
        break;
      case 0x6A:
        sail_setpoint-=0.05;
        if (sail_setpoint<0){sail_setpoint=0;}
        m_boat->sailServo()->set(sail_setpoint);
        break;
      case 0x6B:
        sail_setpoint+=0.05;
        if (sail_setpoint>1){sail_setpoint=1;}
        m_boat->sailServo()->set(sail_setpoint);
        break;
      case 0x6C:
        rudder_setpoint-=0.05;
        if (rudder_setpoint<0){rudder_setpoint=0;}
        m_boat->rudderServo()->set(rudder_setpoint);
        break;
    }
    XBEE_SERIAL.print("rudder: ");XBEE_SERIAL.print(rudder_setpoint);XBEE_SERIAL.print(" | sail: ");XBEE_SERIAL.println(sail_setpoint);
  }
}

void XBEE::logger(){
  while (XBEE_SERIAL.available()<1);
  unsigned char c = XBEE_SERIAL.read();
  if (c==0x6F){
    if (!m_logger->isOpenned()){
      XBEE_SERIAL.print("Openning...\t");
      XBEE_SERIAL.print(m_logger->open());
      XBEE_SERIAL.println(" openned");
    }else{
      XBEE_SERIAL.println("A file is already opened");
    }
  }else if (c==0x63){
    XBEE_SERIAL.println(m_logger->isOpenned());
    XBEE_SERIAL.print(m_logger->close());
    XBEE_SERIAL.println(" entries written.");
  }
}
