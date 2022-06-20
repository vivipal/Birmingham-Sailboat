#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <SD.h>
#include <Config.h>
#include <Sailboat.h>


class Sailboat;


class Logger {

  public:
    Logger();
    ~Logger();
    void init(Sailboat *boat);
    void open();
    void close();
    void flush(){m_file.flush();};

    void write(String msg);
    void write(int val);
    void write(unsigned long int val);
    void write(float val);
    void write(double val);

    String generateFilename();

    void newLog();


  private:
    File m_file;
    String m_filename;
    unsigned long int m_nb_entry;
    unsigned int m_last_log=0;

    Sailboat* m_boat = NULL;
};




#endif
