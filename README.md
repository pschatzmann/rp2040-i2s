# rp2040-i2s

The Rasperry Pico Arduino Core provided by Arduino is based on MBED and does not provide an I2S implementation. 
The core provided by Earl Phil Hower however has one which relies on the [pico-extras](https://github.com/raspberrypi/pico-extras) from RaspberryPI.

I am combining these two solutions as a separate Arduino Library, so that anybody who wants to use the MBED implementation can use I2S as well.

# Installation

You can download the library as zip and call include Library -> zip library. Or you can git clone this project into the Arduino libraries folder e.g. with
```
cd  ~/Documents/Arduino/libraries
git clone pschatzmann/rp2040-i2s.git
```
