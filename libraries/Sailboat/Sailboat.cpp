#include "Sailboat.h"



Sailboat::Sailboat() {
  m_sensor[NAME_IMU] =  new CMPS12();
  m_sensor[NAME_GPS] = new GPS();
  m_sensor[NAME_RC] = new RC();
  m_sensor[NAME_WDIRECTION] = new WindDirection();
  m_sensor[NAME_WSPEED] = new WindSpeed();
  m_xbee = new XBEE();

  m_servo[NAME_RUDDER] = new Servo_Motor(RUDDER_PIN, RUDDER_PWMMIN, RUDDER_PWMMAX, RUDDER_ANGLEMIN, RUDDER_ANGLEMAX);
  m_servo[NAME_SAIL] = new Servo_Motor(SAIL_PIN, SAIL_PWMMIN, SAIL_PWMMAX, SAIL_ANGLEMIN, SAIL_ANGLEMAX);
};

Sailboat::~Sailboat() {
  for (size_t i = 0; i < NB_SENSORS; i++) {
    delete m_sensor[i];
  }
}

void Sailboat::init(Adafruit_PWMServoDriver* servos_pwm){
  for (size_t i = 0; i < NB_SENSORS; i++) {
    m_sensor[i]->init();
  }

  for (size_t i = 0; i < NB_SERVOS; i++) {
    m_servo[i]->init(servos_pwm);
  }
}

WindDirection* Sailboat::wd(){return (WindDirection*) m_sensor[NAME_WDIRECTION];};
WindSpeed* Sailboat::ws(){return (WindSpeed*) m_sensor[NAME_WSPEED];};
CMPS12* Sailboat::compass(){return (CMPS12*) m_sensor[NAME_IMU];};
GPS* Sailboat::gps(){return (GPS*) m_sensor[NAME_GPS];};
RC* Sailboat::rc(){return (RC*) m_sensor[NAME_RC];};
XBEE* Sailboat::xbee(){return (XBEE*) m_xbee;};

Servo_Motor* Sailboat::rudderServo(){return (Servo_Motor*) m_servo[NAME_RUDDER];};
Servo_Motor* Sailboat::sailServo(){return (Servo_Motor*) m_servo[NAME_SAIL];};

void Sailboat::updateSensors(){
  for (size_t i = 0; i < NB_SENSORS; i++) {
    m_sensor[i]->update();
  }
  m_xbee->update();
  updateTrueWindDirection();
}

void Sailboat::updateServos(){
  switch (controlMode()){
    case RADIO_CONTROLLED:
      m_servo[NAME_SAIL]->set( rc()->getValue(SAIL_CHANNEL) );
      m_servo[NAME_RUDDER]->set( rc()->getValue(RUDDER_CHANNEL) );
      break;
    case AUTONOMOUS:
      if (m_controller->status()){
        m_controller->updateCmd();
        m_servo[NAME_SAIL]->set( m_controller->getSailCmd() );
        m_servo[NAME_RUDDER]->set( m_controller->getRudderCmd() );
      }
      break;

  }
}

int Sailboat::controlMode(){return rc()->isReceiving() ? RADIO_CONTROLLED : AUTONOMOUS;}


void Sailboat::updateTrueWindDirection(){

  if (gps()->speedStatus() && gps()->courseStatus()){

    float SOG = gps()->getSpeed();
    float COG = gps()->getCourse()*180/M_PI;

    float AWD = ((int)(wd()->getDirection() + compass()->getAngle())%360)*180/M_PI;
    float AWS = ws()->getSpeed();

    float u = SOG*sin(COG) - AWS*sin(AWD);
    float v = SOG*cos(COG) - AWS*cos(AWD);

    m_true_wind_dir = atan2(u,v);
  } else {
    m_true_wind_dir = -1;
  }

}
