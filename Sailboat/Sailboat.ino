#include "Sailboat.h"

int last_dir=-50, last_angle = -50;
int dir, angle;
float last_speed = -50, spd;
double lati,lon, last_lati=0,last_lon=0;
float steering, throttle;

Sailboat boat;

Logger logger;

Servo_Motor rudderServo(0,143,428,-90,90);
Servo_Motor sailServo(1,151,417,0,2160);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Interrupt function for the anemometer
void AnemometerRotation() { boat.ws()->newRotation(); }
void intCH1() { boat.rc()->interruptCH(2,0); }
void intCH2() { boat.rc()->interruptCH(3,1); }

void setup(){

  Serial.begin(9600);

  boat.init();
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);

  rudderServo.init(&pwm);
  sailServo.init(&pwm);


  pinMode(2, INPUT); attachInterrupt(digitalPinToInterrupt(2), intCH1, CHANGE);
  pinMode(3, INPUT); attachInterrupt(digitalPinToInterrupt(3), intCH2, CHANGE);

  logger.init();
  logger.open();
  logger.write("LOG :\n\n");

  Serial.println("Setup done");
  Serial.println("----------\n");
}



void loop(){
  if (boat.rc()->isReceiving()){
    throttle = boat.rc()->getValue(0);
    steering = boat.rc()->getValue(1);

    rudderServo.set(steering);
    sailServo.set(throttle);

    displayDataB();
  } else  {
    boat.updateSensors();

    dir = boat.wd()->getDirection();
    spd = boat.ws()->getSpeed();
    angle = boat.compass()->getAngle();
    lati = boat.gps()->getLat(); lon = boat.gps()->getLon();

    if(abs(dir - last_dir) > 5 || abs(spd - last_speed) > 0.5 || abs(angle - last_angle) > 0.5|| abs(lati - last_lati) > 0.|| abs(lon - last_lon) > 0.5){
      displayDataA();
      logDataA();
    }
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
  Serial.print(steering);
  Serial.print(";");
  Serial.print(throttle);
  Serial.println("\t");
}
