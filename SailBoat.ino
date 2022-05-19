#include <WindDirection.h>


int last_dir=-50;
int dir;

WindDirection wd; // Sensor for wind direction


void setup(){

  Serial.begin(57600);

  wd.init();
}


void loop(){

  wd.update();

  dir = wd.getDirection();

  if(abs(dir - last_dir) > 5){ displayData(); }
}

void displayData(){

  Serial.print("Direction : ");Serial.print(dir);Serial.print("\t\t");
  Serial.println();

  last_dir=dir;
}
