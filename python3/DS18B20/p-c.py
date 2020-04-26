from ctypes import cdll
import os
import time 
p = os.getcwd() + '/ds18b20.so'
t = cdll.LoadLibrary(p)
t.DS18B20_Init()
while True:
	print(t.DS18B20_Get_Temp())
	time.sleep(1)
