#include <WindDirection.h>
#include <WindSpeed.h>
#include <CMPS12.h>


int last_dir=-50, last_angle = -50;
int dir, angle;
float last_speed = -50, spd;


WindDirection wd; // Sensor for wind direction
WindSpeed ws; // Sensor for wind speed
CMPS12 compass; // Compass sensor

// Interrupt function for the anemometer
void AnemometerRotation() { ws.newRotation(); }

void setup(){

  Serial.begin(57600);

  wd.init();
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);
  compass.init();
}


void loop(){


  wd.update();
  ws.update();
  compass.update();

  dir = wd.getDirection();
  spd = ws.getSpeed();
  angle = compass.getAngle();

  if(abs(dir - last_dir) > 5 || abs(spd - last_speed) > 0.5 || abs(angle - last_angle) > 0.5){
    displayData();
  }
}

void displayData(){

  Serial.print("Direction : ");Serial.print(dir);Serial.print("\t\t");
  Serial.print("Speed : ");Serial.print(spd);Serial.print("\t\t");
  Serial.print("Angle : "); Serial.print(angle);Serial.print("\t\t");
  Serial.println();

  last_dir=dir;
  last_speed=spd;
  last_angle=angle;
}
