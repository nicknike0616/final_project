import paho.mqtt.client as paho
import time
import serial
import locale
import threading

mqttc = paho.Client()
host = "172.16.225.24"
topic= "velocity"
port = 1883

def on_connect(self, mosq, obj, rc):
    print("Connected rc: " + str(rc))

def on_message(mosq, obj, msg):
    print("[Received] Topic: " + msg.topic + ", Message: " + str(msg.payload) + "\n")

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed OK")

def on_unsubscribe(mosq, obj, mid, granted_qos):
    print("Unsubscribed OK")

mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe
mqttc.on_unsubscribe = on_unsubscribe
print("Connecting to " + host + "/" + topic)
mqttc.connect(host, port=1883, keepalive=60)
mqttc.subscribe(topic, 0)
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)
print("start")
mission=[]
number=[]
find_object=[]

while(1):
    line=s.read(1)
    x=line.decode()
    if x=='o':
        line=s.read(1)
        number=line.decode()
    elif x=='m':
        line=s.read(1)
        find_object=int(line.decode())
    elif x=='f':
        break
    else:
        mission.append(int(x))

    time.sleep(0.1)
print("mission:"+str(mission)[1:-1] )
print(" find_object:"+str(find_object)[0] )
print("identify number:"+str(number)[0] )