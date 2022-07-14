#!/bin/sh
ldconfig
export DISPLAY=:0.0
echo 1 > /proc/gpio/mvbReset
cd /project/IDDGUI
chmod +x ppcapp
./ppcapp&
