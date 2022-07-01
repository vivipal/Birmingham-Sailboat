#include <MissionPlanner.h>


MissionPlanner::MissionPlanner(){

}

void MissionPlanner::init(Sailboat* boat){
  m_boat = boat;
  m_wp[0] = m_boat->gps()->getLatLon();

  // Test Mission
  COORD_LATLON tmp;
  tmp.lat =52.48595428857752;
  tmp.lon =-1.8897095942135334;
  m_wp[1] = tmp;

  tmp.lat =52.48549204855041;
  tmp.lon =-1.8892482542629718;
  m_wp[2] = tmp;

  tmp.lat =52.48448043978321;
  tmp.lon =-1.8906108164425373;
  m_wp[3] = tmp;

  tmp.lat =52.48421963906883;
  tmp.lon =-1.8918017172451496;
  m_wp[4] = tmp;


  m_nb_wp = nbWP();

}

int MissionPlanner::nbWP(){
  // doesnt count first wp (home wp)
  int c =  0 ;
  while(m_wp[++c].isDefined());
  return c-1;
}

void MissionPlanner::update(COORD_LATLON m){


  if (waypoint_passed(m)){
    m_nb_wp_passed++;
    // XBEE_SERIAL.print("WP reached, going to ");
    // XBEE_SERIAL.println(m_nb_wp_passed);
    if (m_nb_wp_passed>=m_nb_wp){
      m_boat->attachController(NAME_NONECONTROLLER);
      // XBEE_SERIAL.println("   Mission finished: do None");
    }else{
      // XBEE_SERIAL.print("   Heading to new WP : ");
      COORD_LATLON a = m_wp[m_nb_wp_passed];
      COORD_LATLON b = m_wp[m_nb_wp_passed+1];
      // XBEE_SERIAL.print(a.lat,6);XBEE_SERIAL.print(" ");XBEE_SERIAL.print(a.lon,6);XBEE_SERIAL.print("  ->  ");
      // XBEE_SERIAL.print(b.lat,6);XBEE_SERIAL.print(" ");XBEE_SERIAL.print(b.lon,6);XBEE_SERIAL.print("\n\r");
      m_boat->getFollowLine()->setLine(a,b);
    }
  }
}

int MissionPlanner::waypoint_passed(COORD_LATLON m){
  COORD_XY pwp = coord2cart(m_wp[m_nb_wp_passed]);
  COORD_XY nwp = coord2cart(m_wp[m_nb_wp_passed+1]);
  COORD_XY m_xy = coord2cart(m);

  return (((nwp.x-pwp.x)*(m_xy.x-nwp.x)) > 0 ) ? 1 : 0 ;
}
