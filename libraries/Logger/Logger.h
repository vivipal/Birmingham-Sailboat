#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <SD.h>

#define PIN_SD_CARD 53 // SS pin  (50 (MISO), 51 (MOSI), 52 (SCK))



class Logger {

  public:
    Logger();
    ~Logger();
    void init();
    void open();
    void close();
    void flush(){m_file.flush();};

    void write(String msg);
    void write(int val);
    void write(float val);
    void write(double val);



  private:
    File m_file;
    String m_filename = "test.txt";
};




#endif
