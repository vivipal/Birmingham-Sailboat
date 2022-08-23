#include <Sailboat.h>
#include <MissionPlanner.h>

Sailboat boat;

Logger logger;
MissionPlanner MPlanner;

#define WAYPOINT_NB 7
double mission_coord[WAYPOINT_NB][2] = {{52.42950442279662, -1.9451672734718324},
                                        {52.42961481501567, -1.945328206012726},
                                        {52.429415291099495, -1.945487797449112},
                                        {52.42955021515809, -1.9457573594551087},
                                        {52.42932861239549, -1.946025580356598},
                                        {52.42953958479254, -1.9464265706043244},
                                        {52.42921249537379, -1.9468141498069764}};



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

  logger.init(&boat);
  Serial.println("Logger initialized");
  MPlanner.init(&boat);
  Serial.println("mp initialized");

  boat.attachController(NAME_NONECONTROLLER);
  Serial.println("Controller initialized");

  Serial.println("Setup done"); Serial.println("----------\n");
  XBEE_SERIAL.println("Setup done\n\r----------\n");

  // wait for GPS
  while (boat.gps()->locationStatus()==NOT_VALID){delay(500);};

  // Loading the mission
  boat.getMP()->reset();
  COORD_LATLON tmp;
  for (size_t i = 0; i < WAYPOINT_NB; i++) {
    tmp.lat = mission_coord[i][0];
    tmp.lon = mission_coord[i][1];
    boat.getMP()->setWP(i+1,tmp);
  }
  boat.getMP()->start();

  boat.testServos();

  logger.open();
}



void loop(){
  boat.updateSensors();
  boat.updateServos();
  logger.newLog();
}
