sudo slcand -o -c -s8 -F /dev/ttyACM0 can0 &
sleep 1
sudo ifconfig can0 up
