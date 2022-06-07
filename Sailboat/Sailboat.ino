#include "Sailboat.h"

int last_dir=-50, last_angle = -50;
int dir, angle;
float last_speed = -50, spd;
double lati,lon, last_lati=0,last_lon=0;
float steering, throttle;

Sailboat boat;

Logger logger;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Interrupt function for the anemometer
void AnemometerRotation() { boat.ws()->newRotation(); }
void intCH1() { boat.rc()->interruptCH(RUDDER_CHANNEL_PIN,RUDDER_CHANNEL); }
void intCH2() { boat.rc()->interruptCH(SAIL_CHANNEL_PIN,SAIL_CHANNEL); }

void setup(){

  Serial.begin(9600);

  boat.init(&pwm);

  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);
  pinMode(RUDDER_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(RUDDER_CHANNEL_PIN), intCH1, CHANGE);
  pinMode(SAIL_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(SAIL_CHANNEL_PIN), intCH2, CHANGE);

  logger.init();
  logger.open();
  logger.write("LOG :\n\n");

  Serial.println("Setup done"); Serial.println("----------\n");
}



void loop(){
  switch (boat.controlMode()) {
    case RADIO_CONTROLLED:
      boat.updateServos();
      throttle = boat.rc()->getValue(SAIL_CHANNEL);
      steering = boat.rc()->getValue(RUDDER_CHANNEL);


      displayDataB();
      break;

    case AUTONOMOUS:
      boat.updateSensors();
      dir = boat.wd()->getDirection(); spd = boat.ws()->getSpeed(); angle = boat.compass()->getAngle(); lati = boat.gps()->getLat(); lon = boat.gps()->getLon();
      if(abs(dir - last_dir) > 5 || abs(spd - last_speed) > 0.5 || abs(angle - last_angle) > 0.5|| abs(lati - last_lati) > 0.|| abs(lon - last_lon) > 0.5){
        displayDataA();logDataA();
      }
      break;
  }


}

void displayDataA(){
  Serial.print("Direction : "); Serial.print(dir); Serial.print("\t");
  Serial.print("Speed : "); Serial.print(spd); Serial.print("\t");
  Serial.print("Angle : "); Serial.print(angle); Serial.print("\t");
  Serial.print("Lat : "); Serial.print(lati); Serial.print("\t");
  Serial.print("Lon : "); Serial.print(lon); Serial.print("\t");
  Serial.println();

  last_dir=dir;
  last_speed=spd;
  last_angle=angle;
  last_lon=lon; last_lati=lati;
}

void logDataA(){
  logger.write(dir); logger.write(";");
  logger.write(spd); logger.write(";");
  logger.write(angle); logger.write(";");
  logger.write(lati); logger.write(";");
  logger.write(lon); logger.write("\n");
  logger.flush();
}

void displayDataB(){
  Serial.print(throttle);
  Serial.print(";");
  Serial.print(steering);
  Serial.println("\t");
}
