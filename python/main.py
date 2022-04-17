import serial
import time
arduino = serial.Serial('/dev/cu.usbmodem1301', 9600)  # open serial port
print('Using', arduino.name)         # check which port was really used
data = arduino.readline()
print(str(data))
arduino.write(b'1 NAME:Hold It Down ARTIST:Digga D MIN:2 SEC:31;')
# while True:
#     data = arduino.readline()
#     if data:
#         print(str(data))  # strip out the new lines for now
#         # (better to do .read() in the long run for this reason

# # write a string
# arduino.write(b'1 NAME:Hold It Down ARTIST:Digga D MIN:2 SEC:31')
# time.sleep(3)
# arduino.close()
