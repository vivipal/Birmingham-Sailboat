import serial
from time import sleep
import struct

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)



LatLon_data = [ [52.485, 1.8897095942135334],
                [52.48549204855041, 1.8892482542629718],
                [52.48448043978321, 1.8906108164425373],
                [52.48421963906883, 1.8918017172451496] ]

print(ser.write(struct.pack("c",bytes('m','utf-8'))))
print(ser.write(struct.pack("B",len(LatLon_data))))

for c in LatLon_data:
    data = struct.pack('<f',float(c[0]))
    print(ser.write(data))
    data = struct.pack('<f',float(c[1]))
    print(ser.write(data))
