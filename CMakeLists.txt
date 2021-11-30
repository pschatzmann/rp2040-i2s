#
# cmake file to build the i2s library for the rp2040 pico microcontroller
# for the Pico-Arduino project: https://github.com/pschatzmann/pico-arduino.git
#
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(rp2040-i2s)
pico_sdk_init()

include(FetchContent)
FetchContent_Declare(arduino GIT_REPOSITORY https://github.com/pschatzmann/pico-arduino.git GIT_TAG main)
if(NOT arduino_POPULATED)
  FetchContent_Populate(arduino)
endif()


add_library(rp2040-i2s 
    ${CMAKE_CURRENT_LIST_DIR}/src/I2S.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/pico_audio_i2s/audio_i2s.c 
    ${CMAKE_CURRENT_LIST_DIR}/src/pico_util_buffer/buffer.c
    ${CMAKE_CURRENT_LIST_DIR}/src/pico_audio/audio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/pico_audio/audio_utils.S 
)

## We need the arduino headers to be able to compile
target_include_directories(rp2040-i2s 
  PUBLIC
    "src"
  PRIVATE
    "${arduino_SOURCE_DIR}/Arduino/ArduinoCore-API/api"
    "${arduino_SOURCE_DIR}/Arduino/ArduinoCore-Pico"
    "${arduino_SOURCE_DIR}/Arduino"
)

target_link_libraries(rp2040-i2s 
  pico_stdio_usb 
  pico_stdlib 
  pico_sync
  pico_multicore
  hardware_dma
  hardware_pio
  hardware_irq
  hardware_clocks
  hardware_spi
  hardware_adc
  hardware_pwm
)

