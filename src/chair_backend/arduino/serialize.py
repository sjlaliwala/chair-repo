import serial

arduino = serial.Serial('COM5', 115200, timeout=.1)
while True:
	data = arduino.readline()
	if data:
		print(data.decode("utf-8")) #strip out the new lines for now
		# (better to do .read() in the long run for this reason