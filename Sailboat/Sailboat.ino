#include <Sailboat.h>

#define ENABLE_SERIAL 1


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

  logger.init(&boat,ENABLE_SERIAL); logger.open();

  Serial.println("Setup done"); Serial.println("----------\n");
}



void loop(){
  switch (boat.controlMode()) {
    case RADIO_CONTROLLED:
      boat.updateServos();
      break;

    case AUTONOMOUS:
      boat.updateSensors();
      break;
  }
  logger.newLog();
}
