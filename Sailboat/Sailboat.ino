#include <Sailboat.h>
#include <FollowLine.h>

Sailboat boat;

Logger logger;

FollowLine c(&boat);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Interrupt function for the anemometer
void AnemometerRotation() { boat.ws()->newRotation(); }
void intCH1() { boat.rc()->interruptCH(RUDDER_CHANNEL_PIN,RUDDER_CHANNEL); }
void intCH2() { boat.rc()->interruptCH(SAIL_CHANNEL_PIN,SAIL_CHANNEL); }

void setup(){

  Serial.begin(57600);

  boat.init(&pwm);
  boat.attachedController(&c);
  c.setLine(52.4884112,-1.886354,52.487302,-1.885140,5);

  attachInterrupt(digitalPinToInterrupt(WIND_SPEED_PIN), AnemometerRotation, FALLING);
  pinMode(RUDDER_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(RUDDER_CHANNEL_PIN), intCH1, CHANGE);
  pinMode(SAIL_CHANNEL_PIN, INPUT); attachInterrupt(digitalPinToInterrupt(SAIL_CHANNEL_PIN), intCH2, CHANGE);

  logger.init(&boat); logger.open();
  boat.xbee()->init(&boat);

  Serial.println("Setup done"); Serial.println("----------\n");
}



void loop(){
  boat.updateSensors();
  boat.updateServos();
  logger.newLog();
}
