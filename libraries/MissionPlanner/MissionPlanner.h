#ifndef __MISSIONPLANNER_H__
#define __MISSIONPLANNER_H__

#include <Config.h>
#include <tools.h>
#include <Sailboat.h>

class Sailboat;

#define MAX_WAYPOINTS 10

class MissionPlanner {
  public:
    MissionPlanner();

    void init(Sailboat* boat);

    int nbWP();
    void setWP(int nb, COORD_LATLON c);
    void reset();
    void start();
    int nb_wp_passed(){return m_nb_wp_passed;}
    void update();
    void update(COORD_LATLON m);
    int waypoint_passed(COORD_LATLON m);
    void printWPs(){
      for (size_t i = 0; i < MAX_WAYPOINTS+1; i++) {
        Serial.print(m_wp[i].lat,6);
        Serial.print(" ");
        Serial.println(m_wp[i].lon,6);
      }
    }


  private:
    COORD_LATLON m_wp[MAX_WAYPOINTS+1];

    int m_nb_wp_passed = 0;
    int m_nb_wp = 0;

    Sailboat* m_boat = NULL;
};



#endif
