#ifndef __RCRECEIVER_H__
#define __RCRECEIVER_H__


#define CHANNEL_NB 2 // we are considering only 2 channels

class RC {
  public :

    RC();


    void interruptCH(int pin, int channel);

    float getRawValue(int channel);
    float getFilteredValue(int channel);
    float getValue(int channel);

    int isReceiving();


  private :
    unsigned long m_start_time[CHANNEL_NB];
    unsigned long m_raw_value[CHANNEL_NB];
    unsigned long m_filtered_value[CHANNEL_NB];
    float m_value[CHANNEL_NB];

    float m_offsetmax[CHANNEL_NB];
    float m_offsetmin[CHANNEL_NB];

    unsigned int m_last_interrupt;




};



#endif
