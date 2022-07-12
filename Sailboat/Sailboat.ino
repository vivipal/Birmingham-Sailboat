#include <Sailboat.h>
#include <XBEE.h>
#include <MissionPlanner.h>

Sailboat boat;

Logger logger;
XBEE xbee;
MissionPlanner MPlanner;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Interrupt function for the anemometer
void AnemometerRotation() { boat.ws()->newRotation(); }
void intCH1() { boat.rc()->interruptCH(RUDDER_CHANNEL_PIN,RUDDER_CHANNEL); }
void intCH2() { boat.rc()->interruptCH(SAIL_CHANNEL_PIN,SAIL_CHANNEL); }

void setup(){

  Serial.begin(57600);
  Serial.println("Serial initialized");

  boat.init(&pwm, &MPlanner);
  Serial.println("Boat initialized");


  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);
  pinMode(RUDDER_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(RUDDER_CHANNEL_PIN), intCH1, CHANGE);
  pinMode(SAIL_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(SAIL_CHANNEL_PIN), intCH2, CHANGE);
  Serial.println("Servos initialized");

  logger.init(&boat); logger.open();
  Serial.println("Logger initialized");
  xbee.init(&boat);
  Serial.println("XBEE initialized");
  while (boat.gps()->locationStatus()==NOT_VALID);
  MPlanner.init(&boat);
  Serial.println("mp initialized");

  boat.attachController(NAME_NONECONTROLLER);
  Serial.println("Controller initialized");

  Serial.println("Setup done"); Serial.println("----------\n");
  XBEE_SERIAL.println("Setup done\n\r----------\n");

  boat.testServos();
}



void loop(){
  boat.updateSensors();
  boat.updateServos();
  logger.newLog();
  xbee.update();
}
