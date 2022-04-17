import serial
ser = serial.Serial('/dev/ttyUSB0')  # open serial port
ser.baudrate = 9600
print(ser.name)         # check which port was really used
ser.write(b'hello')     # write a string
ser.close()

# Windows method
# https://stackoverflow.com/questions/65011660/how-can-i-get-the-title-of-the-currently-playing-media-in-windows-10-with-python