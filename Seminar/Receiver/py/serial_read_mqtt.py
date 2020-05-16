import serial
import paho.mqtt.client as mqtt

BROKER = "mqtt.eclipse.org"
CLIENTID = "MQTTExample"
TOPIC_ONE = "A507/sensors/distance"
TOPIC_TWO = "A507/sensors/light"
COMPORT = "COM6" # please replace this with your port number
QOS = 1

import time

mqttc = mqtt.Client(CLIENTID)
mqttc.connect(BROKER)

ser = serial.Serial(COMPORT, 115200, timeout=5) 
while True:
	message = ser.readline()
	print (message)
	if b'D:' in message:
		string, distance = message.split(b' ')
		mqttc.publish(TOPIC_ONE, payload=distance.decode('utf-8'), qos=QOS, retain=False)
	if b'L:' in message:
		string, light = message.split(b' ')
		mqttc.publish(TOPIC_TWO, payload=light.decode('utf-8'), qos=QOS, retain=False)
	time.sleep(0.01)
mqttc.disconnect()
time.sleep(1)