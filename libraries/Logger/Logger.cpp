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

String Logger::open(){
  m_filename = generateFilename();
  m_file = SD.open(m_filename, FILE_WRITE);
  m_nb_entry=0;
  m_last_log = millis();
  return m_filename;
}

unsigned long int Logger::close(){
  m_file.flush();
  m_file.close();
  m_filename = "";
  return m_nb_entry;
}

void Logger::write(String msg){
  if (ENABLE_LOGGING && m_file!=NULL && (m_time-m_last_log)>LOG_PERIOD){m_file.print(msg);}
  if (ENABLE_SERIAL){Serial.print(msg); }
  if (ENABLE_XBEE && (m_time-m_last_xbee)>XBEE_PERIOD){XBEE_SERIAL.print(msg);}
}
void Logger::write(int val){
  if (ENABLE_LOGGING && m_file!=NULL && (m_time-m_last_log)>LOG_PERIOD){m_file.print(val);}
  if (ENABLE_SERIAL){Serial.print(val); }
  if (ENABLE_XBEE && (m_time-m_last_xbee)>XBEE_PERIOD){XBEE_SERIAL.print(val);}
}
void Logger::write(unsigned long int val){
  if (ENABLE_LOGGING && m_file!=NULL && (m_time-m_last_log)>LOG_PERIOD){m_file.print(val);}
  if (ENABLE_SERIAL){Serial.print(val); }
  if (ENABLE_XBEE && (m_time-m_last_xbee)>XBEE_PERIOD){XBEE_SERIAL.print(val);}
}
void Logger::write(float val){
  if (ENABLE_LOGGING && m_file!=NULL && (m_time-m_last_log)>LOG_PERIOD){m_file.print(val,5);}
  if (ENABLE_SERIAL){Serial.print(val,5); }
  if (ENABLE_XBEE && (m_time-m_last_xbee)>XBEE_PERIOD){XBEE_SERIAL.print(val,5);}
}
void Logger::write(double val){
  if (ENABLE_LOGGING && m_file!=NULL && (m_time-m_last_log)>LOG_PERIOD){m_file.print(val,8);}
  if (ENABLE_SERIAL){Serial.print(val,8); }
  if (ENABLE_XBEE && (m_time-m_last_xbee)>XBEE_PERIOD){XBEE_SERIAL.print(val,8);}
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


  if ((m_boat)){

    m_time = millis();

    write(m_boat->controlMode());write(";"); // control mode of the boat

    write(m_boat->gps()->getD());write(m_boat->gps()->getM());write(m_boat->gps()->getY());write("-"); // date
    write(m_boat->gps()->geth());write(m_boat->gps()->getm());write(m_boat->gps()->gets());write(";"); //time


    write(m_boat->wd()->getDirection());write(";"); // direction opf the wind
    write(m_boat->ws()->getSpeed());write(";"); // speed of the wind
    write(m_boat->compass()->getAngle());write(";"); // heading of the boat
    write(m_boat->gps()->getSpeed());write(";"); // speed of the boat (gps)

    write(m_boat->gps()->getLat());write(";"); // latitude
    write(m_boat->gps()->getLon());write(";"); // longitude

    write(m_boat->sailServo()->getLastSet());write(";");
    write(m_boat->rudderServo()->getLastSet());write(";");

    write("\n\r");

    // Serial.println((millis()-m_last_log));
    if ((millis()-m_last_log)>LOG_PERIOD && ENABLE_LOGGING && m_file!=NULL){m_nb_entry++;m_last_log=millis();}
    if ((millis()-m_last_xbee)>XBEE_PERIOD){m_last_xbee=millis();}

  }
  flush();
}
