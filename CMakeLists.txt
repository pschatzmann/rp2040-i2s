cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(rp2040-i2s)
pico_sdk_init()

## fetch arduino headers
include(FetchContent)
FetchContent_Declare(arduino GIT_REPOSITORY https://github.com/pschatzmann/pico-arduino.git GIT_TAG main)
FetchContent_Populate(arduino)

add_library(rp2040-i2s 
    src/I2S.cpp 
    src/pico_audio_i2s/audio_i2s.c 
    src/pico_util_buffer/buffer.c
#    src/pico_audio/audio.cpp 
    src/pico_audio/audio_utils.S 
)

## We need the arduino headers to be able to compile
target_include_directories(rp2040-i2s PUBLIC
    "src"
    "${arduino_SOURCE_DIR}/Arduino"
    "${arduino_SOURCE_DIR}/Arduino/ArduinoCore-API/api" 
    "${arduino_SOURCE_DIR}/Arduino/ArduinoCore-Pico"
)

target_link_libraries(rp2040-i2s 
  pico_stdio_usb 
  pico_stdlib 
  pico_runtime
  pico_multicore 
  pico_util 
  pico_unique_id
  hardware_clocks
  hardware_dma
  hardware_irq
  hardware_spi
  hardware_adc
  hardware_pwm
  hardware_pio
  hardware_gpio
)

