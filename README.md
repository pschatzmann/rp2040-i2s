# rp2040-i2s

The Rasperry Pico Core implementation provided by Arduino is based on MBED and does not have any I2S implementation. 
The [core from Earle Phil Hower](https://github.com/earlephilhower/arduino-pico) however has one which relies on the [pico-extras](https://github.com/raspberrypi/pico-extras) from RaspberryPI.

I am combining these two solutions as a separate Arduino Library, so that it can be used with the [Pico-Arduino](https://github.com/pschatzmann/pico-arduino.git) Library.


### Documentation

[Here is the class documentation](https://pschatzmann.github.io/rp2040-i2s/html/class_i2_s_class.html)


### Installation

You can download the library as zip and call include Library -> zip library. Or you can git clone this project into the Arduino libraries folder e.g. with
```
cd  ~/Documents/Arduino/libraries
git clone pschatzmann/rp2040-i2s.git
```
