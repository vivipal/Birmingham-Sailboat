# Using python

Just run the .py script (and modify lat lon coords directly in the script)


# Using c++ and a mission file

## How to build it

```console
g++ main.cpp -o send_mission.exe
```


## How to use it

This program send a mission to the arduino via the xbee. The mission is just a list of waypoints

### Mission file

Your mission file should look like this

```txt
lat1 lon1
lat2 lon2
lat3 lon3
lat4 lon4
lat5 lon5
```

See example_mission.txt for a real example

### Send the mission

```console
./send_mission.exe /dev/[XBEE_DEVICE] [mission_file]
```
