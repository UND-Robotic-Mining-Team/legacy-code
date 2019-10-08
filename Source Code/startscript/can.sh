#!/bin/sh

sudo slcand -o -c -s8 /dev/serial/by-id/*CANtact*-if00 can0
sleep 1
sudo ifconfig can0 up
sleep 1
sudo ifconfig can0 txqueuelen 1000
