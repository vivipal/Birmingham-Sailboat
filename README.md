# Hardware

This code has been developped for an Arduino MEGA 2560

Every sensor configuration can be found in *libraries/Sailboat/Config.h*

Here is how the wiring is done :

![Wiring Diagram](images/wiring_diagram.svg)

# Requirement

The following Arduino libraries are required:
- TinyGPSPlus (v1.0.3)
- Adafruit PWM Servo Driver (v2.4.1)
- SD (v1.2.4)
- SoftwareSerial (v1.0) *[installed with Arduino IDE]*
- Wire (v1.0) *[installed with Arduino IDE]*
- SPI (v1.0) *[installed with Arduino IDE]*




# Build

```
git clone https://github.com/vivipal/Birmingham-Sailboat
```

Make sure that your have installed Arduino IDE and installed all the libraries required the managing libraries tool. Then you have to copy every folders in libraries/ into your Arduino libraries folder:

For Linux :
```console
cd Birmingham-Sailboat
cp -r libraries/* ~/Arduino/libraries/
```

You should now be able to build the .ino codes using Arduino IDE.

# Sailboat.ino VS Sailboat_Ready2Go.ino
