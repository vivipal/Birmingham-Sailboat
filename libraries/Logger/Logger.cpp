#include "Logger.h"



Logger::Logger(){

}


Logger::~Logger(){
  close();
}

void Logger::init(){
  SD.begin(PIN_SD_CARD);
}

void Logger::open(){
  m_file = SD.open(m_filename, FILE_WRITE);
}

void Logger::close(){
  m_file.flush();
  m_file.close();
}

void Logger::write(String msg){
  m_file.print(msg);
}

void Logger::write(int val){
  m_file.print(val);
}

void Logger::write(float val){
  m_file.print(val);
}

void Logger::write(double val){
  m_file.print(val);
}
