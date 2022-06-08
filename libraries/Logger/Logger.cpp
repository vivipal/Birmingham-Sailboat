#include "Logger.h"



Logger::Logger(){

}


Logger::~Logger(){
  close();
}

void Logger::init(){
  SD.begin(PIN_SD_CARD);
  SD.mkdir("LOG");
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
