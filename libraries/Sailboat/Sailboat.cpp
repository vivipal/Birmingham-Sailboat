#include "Sailboat.h"



Sailboat::Sailboat() {
  m_sensor[NAME_IMU] =  new CMPS12();
  m_sensor[NAME_GPS] = new GPS();
  m_sensor[NAME_RC] = new RC();
  m_sensor[NAME_WDIRECTION] = new WindDirection();
  m_sensor[NAME_WSPEED] = new WindSpeed();

  m_servo[NAME_RUDDER] = new Servo_Motor(RUDDER_PIN, RUDDER_PWMMIN, RUDDER_PWMMAX, RUDDER_ANGLEMIN, RUDDER_ANGLEMAX);
  m_servo[NAME_SAIL] = new Servo_Motor(SAIL_PIN, SAIL_PWMMIN, SAIL_PWMMAX, SAIL_ANGLEMIN, SAIL_ANGLEMAX);

  m_controllers[NAME_LINEFOLLOW] = new FollowLine();
  m_controllers[NAME_NONECONTROLLER] = new NoneController();
};

Sailboat::~Sailboat() {
  for (size_t i = 0; i < NB_SENSORS; i++) {
    delete m_sensor[i];
  }
}

void Sailboat::init(Adafruit_PWMServoDriver* servos_pwm, MissionPlanner* mp){
  for (size_t i = 0; i < NB_SENSORS; i++) {
    m_sensor[i]->init();
  }

  for (size_t i = 0; i < NB_SERVOS; i++) {
    m_servo[i]->init(servos_pwm);
  }
  m_controllers[NAME_LINEFOLLOW]->init(this);
  m_missionplanner = mp;
}

WindDirection* Sailboat::wd(){return (WindDirection*) m_sensor[NAME_WDIRECTION];};
WindSpeed* Sailboat::ws(){return (WindSpeed*) m_sensor[NAME_WSPEED];};
CMPS12* Sailboat::compass(){return (CMPS12*) m_sensor[NAME_IMU];};
GPS* Sailboat::gps(){return (GPS*) m_sensor[NAME_GPS];};
RC* Sailboat::rc(){return (RC*) m_sensor[NAME_RC];};

Servo_Motor* Sailboat::rudderServo(){return (Servo_Motor*) m_servo[NAME_RUDDER];};
Servo_Motor* Sailboat::sailServo(){return (Servo_Motor*) m_servo[NAME_SAIL];};

FollowLine* Sailboat::getFollowLine(){return (FollowLine*) m_controllers[NAME_LINEFOLLOW];}

void Sailboat::updateSensors(){
  for (size_t i = 0; i < NB_SENSORS; i++) {
    m_sensor[i]->update();
  }
  updateTrueWindDirection();
  getMP()->update();

  while(rc()->isReceiving()){
    m_servo[NAME_SAIL]->set( rc()->getValue(SAIL_CHANNEL) );
    m_servo[NAME_RUDDER]->set( rc()->getValue(RUDDER_CHANNEL) );
  }
}

void Sailboat::updateServos(){
  switch (controlMode()){
    case RADIO_CONTROLLED:
      break;
    case AUTONOMOUS:
      if (m_current_controller->status()){
        m_current_controller->updateCmd();
        m_servo[NAME_SAIL]->set( m_current_controller->getSailCmd() );
        m_servo[NAME_RUDDER]->set( m_current_controller->getRudderCmd() );
      }
      break;

  }
}

void Sailboat::testServos(){
  delay(2000);
  Serial.println("Servos test started.");
  m_servo[NAME_SAIL]->set( 0 );
  Serial.println("  Sail to 0");
  delay(5000);
  m_servo[NAME_RUDDER]->set( 0 );
  Serial.println("  Rudder to 0");
  delay(5000);
  m_servo[NAME_SAIL]->set( 1 );
  Serial.println("  Sail to 1");
  delay(5000);
  m_servo[NAME_RUDDER]->set( 1 );
  Serial.println("  Rudder to 1");
  delay(5000);
  Serial.println("Servos test finished.");
}

int Sailboat::controlMode(){return rc()->isReceiving() ? RADIO_CONTROLLED : AUTONOMOUS;}


void Sailboat::updateTrueWindDirection(){

  float SOG = gps()->speedStatus() ? gps()->getSpeed() : 0;
  float COG = gps()->courseStatus() ? gps()->getCourse()*180/M_PI : compass()->getAngle()/180*M_PI;

  float AWD = ((float)(((int)(wd()->getDirection() + compass()->getAngle()))%360))/180*M_PI;
  float AWS = ws()->getSpeed();

  float u = -SOG*sin(COG) + AWS*sin(AWD);
  float v = -SOG*cos(COG) + AWS*cos(AWD);

  m_true_wind_dir = (float)(((int)((atan2(u,v)+2*M_PI)*180/M_PI))%360);

}


void Sailboat::attachController(int controller_name){
  m_current_controller = m_controllers[controller_name];
}
