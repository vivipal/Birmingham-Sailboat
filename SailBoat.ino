#include <WindDirection.h>


int last_dir=-50, last_speed = -50;
int dir, spd;

WindDirection wd; // Sensor for wind direction
WindSpeed ws; // Sensor for wind speed


// Interrupt function for the anemometer
void AnemometerRotation() { ws.newRotation(); }

void setup(){

  Serial.begin(57600);

  wd.init();
  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);
}


void loop(){

  wd.update();
  ws.update();

  dir = wd.getDirection();
  spd = ws.getSpeed();

  if(abs(dir - last_dir) > 5 || abs(spd - last_speed) > 0.5){
    displayData();
  }
}

void displayData(){

  Serial.print("Direction : ");Serial.print(dir);Serial.print("\t\t");
  Serial.print("Speed : ");Serial.print(spd);Serial.print("\t\t");
  Serial.println();

  last_dir=dir;
  last_speed=spd;
}
