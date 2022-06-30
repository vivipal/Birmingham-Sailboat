#include <Sailboat.h>
#include <XBEE.h>

Sailboat boat;

Logger logger;
XBEE xbee;

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
  xbee.init(&boat);

  boat.attachController(NAME_LINEFOLLOW);
  boat.getFollowLine()->setLine(52.485974,-1.889489,52.486062,-1.887799);

  Serial.println("Setup done"); Serial.println("----------\n");
  XBEE_SERIAL.println("Setup done\n\r----------\n");
}



void loop(){
  boat.updateSensors();
  boat.updateServos();
  logger.newLog();
  xbee.update();
}
