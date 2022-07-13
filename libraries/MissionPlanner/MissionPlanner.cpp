#include <MissionPlanner.h>


MissionPlanner::MissionPlanner(){

}

void MissionPlanner::init(Sailboat* boat){
  m_boat = boat;
  m_wp[0] = m_boat->gps()->getLatLon();

  m_nb_wp = nbWP();

}

int MissionPlanner::nbWP(){
  // doesnt count first wp (home wp)
  int c =  0 ;
  while(m_wp[++c].isDefined());
  return c-1;
}

void MissionPlanner::setWP(int nb, COORD_LATLON c){
  m_wp[nb] = c;
  m_nb_wp = nbWP();
}

void MissionPlanner::reset(){
  /*
    Remove all waypoints and set current position as home
  */
  COORD_LATLON tmp;
  tmp.lat = 0.0;
  tmp.lon = 0.0;
  for (size_t i = 1; i < MAX_WAYPOINTS+1; i++) {
    m_wp[i] = tmp;
  }
  m_wp[0] = m_boat->gps()->getLatLon();
  m_nb_wp = nbWP();
  m_nb_wp_passed = 0;

}

void MissionPlanner::start(){
  if (m_nb_wp > 1){
    COORD_LATLON a = m_wp[0];
    COORD_LATLON b = m_wp[1];
    m_boat->getFollowLine()->setLine(a,b);
  }
}

void MissionPlanner::update(){
  update(m_boat->gps()->getLatLon());
}

void MissionPlanner::update(COORD_LATLON m){


  if (waypoint_passed(m) && (m_nb_wp>0)){
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
