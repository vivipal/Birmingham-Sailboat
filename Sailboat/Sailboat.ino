#include <Sailboat.h>

Sailboat boat;

Logger logger;


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Interrupt function for the anemometer
void AnemometerRotation() { boat.ws()->newRotation(); }
void intCH1() { boat.rc()->interruptCH(RUDDER_CHANNEL_PIN,RUDDER_CHANNEL); }
void intCH2() { boat.rc()->interruptCH(SAIL_CHANNEL_PIN,SAIL_CHANNEL); }

void setup(){

  Serial.begin(57600);

  boat.init(&pwm);

  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);
  pinMode(RUDDER_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(RUDDER_CHANNEL_PIN), intCH1, CHANGE);
  pinMode(SAIL_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(SAIL_CHANNEL_PIN), intCH2, CHANGE);

  logger.init(&boat); logger.open();

  boat.attachController(NAME_LINEFOLLOW);
  boat.getFollowLine()->setLine(52.483617,-1.676102,52.483617,-1.676102);

  Serial.println("Setup done"); Serial.println("----------\n");
  XBEE_SERIAL.println("Setup done\n\r----------\n");
}



void loop(){
  boat.updateSensors();
  boat.updateServos();
  logger.newLog();
}
