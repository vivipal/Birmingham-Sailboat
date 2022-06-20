#include "Logger.h"



Logger::Logger(){

}


Logger::~Logger(){
  close();
}

void Logger::init(Sailboat *boat){
  SD.begin(PIN_SD_CARD);
  SD.mkdir("LOG");

  m_boat = boat;
  m_nb_entry = 0;
}

void Logger::open(){
  m_filename = generateFilename();
  m_file = SD.open(m_filename, FILE_WRITE);
}

void Logger::close(){
  m_file.flush();
  m_file.close();
  m_filename = "";
}

void Logger::write(String msg){
  if (ENABLE_LOGGING){m_file.print(msg);}
  if (ENABLE_SERIAL){Serial.print(msg); }
}
void Logger::write(int val){
  if (ENABLE_LOGGING){m_file.print(val);}
  if (ENABLE_SERIAL){Serial.print(val); }
}
void Logger::write(unsigned long int val){
  if (ENABLE_LOGGING){m_file.print(val);}
  if (ENABLE_SERIAL){Serial.print(val); }
}
void Logger::write(float val){
  if (ENABLE_LOGGING){m_file.print(val,5);}
  if (ENABLE_SERIAL){Serial.print(val,5); }
}
void Logger::write(double val){
  if (ENABLE_LOGGING){m_file.print(val,8);}
  if (ENABLE_SERIAL){Serial.print(val,8); }
}

String Logger::generateFilename() {
  String extension = ".TXT";

  int k = 1;

  String SDFileName;
  do  {
    SDFileName = "LOG/LOG";
    int n_zero = 4-(int)log10(k);

    for (size_t i = 0; i < n_zero; i++) { SDFileName += "0"; }
    SDFileName +=  String(k) + extension;

    k ++;
  } while (SD.exists(SDFileName));


  return SDFileName;
}

void Logger::newLog(){


  if ((m_boat) && ((millis()-m_last_log)>LOG_PERIOD)){
    m_last_log = millis();

    write(m_boat->controlMode());write(";"); // control mode of the boat

    write(m_boat->gps()->getD());write(m_boat->gps()->getM());write(m_boat->gps()->getY());write("-"); // date
    write(m_boat->gps()->geth());write(m_boat->gps()->getm());write(m_boat->gps()->gets());write(";"); //time


    write(m_boat->wd()->getDirection());write(";"); // direction opf the wind
    write(m_boat->ws()->getSpeed());write(";"); // speed of the wind
    write(m_boat->compass()->getAngle());write(";"); // heading of the boat
    write(m_boat->gps()->getSpeed());write(";"); // speed of the boat (gps)

    write(m_boat->gps()->getLat());write(";"); // latitude
    write(m_boat->gps()->getLon());write(";"); // longitude

    if (m_boat->controlMode()==RADIO_CONTROLLED) {
      write(m_boat->rc()->getValue(SAIL_CHANNEL));write(";"); // sail command
      write(m_boat->rc()->getValue(RUDDER_CHANNEL));write(";"); // rudder command
    }
    write("\n\r");
    m_nb_entry++;
  }
  flush();
}
