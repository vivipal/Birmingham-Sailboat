#include <WindDirection.h>
#include <WindSpeed.h>
#include <CMPS12.h>
#include <GPS.h>
#include <ServoController.h>


int last_dir=-50, last_angle = -50;
int dir, angle;
float last_speed = -50, spd;
double lati,lon, last_lati=0,last_lon=0;


WindDirection wd; // Sensor for wind direction
WindSpeed ws; // Sensor for wind speed
CMPS12 compass; // Compass sensor
GPS gps; // gps
Servo_Motor rudderServo(0,143,428,-90,90);
Servo_Motor sailServo(1,151,417,0,2160);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Interrupt function for the anemometer
void AnemometerRotation() { ws.newRotation(); }

void setup(){

  Serial.begin(57600);

  wd.init();
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);
  compass.init();
  gps.init();
  rudderServo.init(&pwm);
  sailServo.init(&pwm);

  
  testServo();

  
  Serial.println("Setup done");
  Serial.println("----------\n");
}



void loop(){



  wd.update(); ws.update(); compass.update(); gps.update();

  dir = wd.getDirection();
  spd = ws.getSpeed();
  angle = compass.getAngle();
  lati = gps.getLat(); lon = gps.getLon();

  if(abs(dir - last_dir) > 5 || abs(spd - last_speed) > 0.5 || abs(angle - last_angle) > 0.5|| abs(lati - last_lati) > 0.|| abs(lon - last_lon) > 0.5){
    displayData();
  }
}

void displayData(){

  Serial.print("Direction : "); Serial.print(dir); Serial.print("\t\t");
  Serial.print("Speed : "); Serial.print(spd); Serial.print("\t\t");
  Serial.print("Angle : "); Serial.print(angle); Serial.print("\t\t");
  Serial.print("Lat : "); Serial.print(lati); Serial.print("\t\t");
  Serial.print("Lon : "); Serial.print(lon); Serial.print("\t\t");
  Serial.println();

  last_dir=dir;
  last_speed=spd;
  last_angle=angle;
  last_lon=lon; last_lati=lati;
}


void testServo(){

  /*
   * Open Serial Plotter to see the command of each servo
   */

  
  for (uint16_t pulselen = rudderServo.minPWM(); pulselen < rudderServo.maxPWM(); pulselen++) {
    rudderServo.setPWM(pulselen);
    Serial.print(pulselen);Serial.print("\t");Serial.println(sailServo.minPWM());delay(10);
  }delay(500);
  
  for (uint16_t pulselen = sailServo.minPWM(); pulselen < sailServo.maxPWM(); pulselen++) {
    sailServo.setPWM(pulselen);
    Serial.print(rudderServo.maxPWM());Serial.print("\t");Serial.println(pulselen);delay(10);
  }delay(500);

  for (uint16_t pulselen = rudderServo.maxPWM(); pulselen > rudderServo.minPWM(); pulselen--) {
    rudderServo.setPWM(pulselen);
    Serial.print(pulselen);Serial.print("\t");Serial.println(sailServo.maxPWM());delay(10);
  }delay(500);
  
  for (uint16_t pulselen = sailServo.maxPWM(); pulselen > sailServo.minPWM(); pulselen--) {
    sailServo.setPWM(pulselen);
    Serial.print(rudderServo.minPWM());Serial.print("\t");Serial.println(pulselen);delay(10);
  }delay(500);

}
