#!/usr/bin/python

import serial
from datetime import datetime


CONSOLE = serial.Serial('/dev/ttyACM0', 9600)


while True:
     print datetime.now(), CONSOLE.readline()
