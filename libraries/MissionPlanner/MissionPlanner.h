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
    void update(COORD_LATLON m);
    int waypoint_passed(COORD_LATLON m);


  private:
    COORD_LATLON m_wp[MAX_WAYPOINTS+1];

    int m_nb_wp_passed = 0;
    int m_nb_wp = 0;

    Sailboat* m_boat = NULL;
};



#endif
