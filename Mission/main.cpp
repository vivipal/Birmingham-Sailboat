#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <termios.h> /* POSIX terminal control definitions */


#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>


int open_port(char *device){

  int fd; /* File descriptor for the port */

  fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1){
    printf("Unable to open %s\n", device);
  }else{
    fcntl(fd, F_SETFL, 0);
  }
  return (fd);
}

void setup_serial(int fd){
  struct termios options;

  //Get the current options for the port...
  tcgetattr(fd, &options);

  //Set the baud rates to 9600...
  cfsetispeed(&options, B9600);
  cfsetospeed(&options, B9600);

  // Enable the receiver and set local mode...
  options.c_cflag |= (CLOCAL | CREAD);

  // Set 8N1
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  // Read data as raw
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  // options.c_lflag &= ~(ECHO);

  // set timeout 0.5s
  options.c_cc[VTIME] = 5;

  // Set the new options for the port...
  tcsetattr(fd, TCSANOW, &options);
}


int main(int argc, char const *argv[]){

  /*
    Mission file must look like this :

    l1|  52.48595428857752 -1.8897095942135334
    l2|  52.48549204855041 -1.8892482542629718
    l3|  52.48448043978321 -1.8906108164425373


  */



  char *serial_device = (char*)malloc(30);
  char *mission_file = (char*)malloc(100);
  if (argc!=3){
    std::cout << "Please provide serial port and mission file\nexample: ./send_mission.exe /dev/ttyUSB0 mission.txt." << std::endl;
    return 1;
  }else{
    strcpy(serial_device, argv[1]);
    strcpy(mission_file, argv[2]);
  }


  std::ifstream file;            // creates stream file
 	file.open(mission_file);       // opens .txt file

  std::vector<float> coords; // this vector will contain every coords (coord[0] = lat0, coord[1] = lon0 , coord[2] = lat1 etc..)
  float f;
  while(file >> f){coords.push_back(f);} // save every lat lon in order in a vector


  // open serial communication
  int fd = open_port(serial_device);
  setup_serial(fd);

  // send 'm' to signal a new mission
  char buffer[2] = {'m'};
  write(fd,buffer,1);


  // send the number of waypoint of the mission
  uint8_t number_wp = (uint8_t) coords.size()/2;
  uint8_t* p_nbwp = (uint8_t*) &number_wp;
  write(fd,p_nbwp,1);



  // send every coord
  uint8_t* p_coord;
  for (size_t i = 0; i < coords.size(); i++) {
    p_coord = (uint8_t*) &coords[i];
    write(fd,p_coord,4);
  }

  file.close();
  free(serial_device); // close connection
}
