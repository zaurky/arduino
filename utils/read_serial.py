#!/usr/bin/python

import argparse
from datetime import datetime
import serial
import time


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-D', '--device', dest='device', default='/dev/ttyACM0')
    parser.add_argument('-b', dest='baud', default=9600)
    args = parser.parse_args()

    console = serial.Serial(args.device, args.baud)

    while True:
        try:
            line = console.readline().rstrip('\n')
            print datetime.now(), line
        except serial.serialutil.SerialException:
            print "deconnected"
            console.close();
            time.sleep(10);
            console.open();
