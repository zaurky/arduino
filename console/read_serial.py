#!/usr/bin/python

import argparse
from datetime import datetime
import serial


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-D', '--device', dest='device', default='/dev/ttyACM0')
    parser.add_argument('-b', dest='baud', default=9600)
    args = parser.parse_args()

    console = serial.Serial(args.device, args.baud)

    while True:
        line = console.readline().rstrip('\n')
        print datetime.now(), line
