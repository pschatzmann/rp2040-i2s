cmake_minimum_required(VERSION 3.13)
#set(CMAKE_TOOLCHAIN_FILE $ENV{PICO_SDK_PATH}/cmake/preload/toolchains/pico_arm_clang.cmake)

set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DPICO_BUFFER_USB_ALLOC_HACK)   
add_compile_options(-Wall
    -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
    -Wno-unused-function # we have some for the docs that aren't called
    -Wno-maybe-uninitialized
)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(rp2040-i2s)
pico_sdk_init()

## fetch arduino headers
#include(FetchContent)
#FetchContent_Declare(arduino GIT_REPOSITORY https://github.com/pschatzmann/pico-arduino.git GIT_TAG main)
#FetchContent_Populate(arduino)

add_library(rp2040-i2s 
    ${CMAKE_CURRENT_LIST_DIR}/src/I2S.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/pico_audio_i2s/audio_i2s.c 
    ${CMAKE_CURRENT_LIST_DIR}/src/pico_util_buffer/buffer.c
    ${CMAKE_CURRENT_LIST_DIR}/src/pico_audio/audio.cpp
#    src/pico_audio/audio_utils.S 
    $<$<NOT:$<BOOL:${PICO_NO_HARDWARE}>>:${CMAKE_CURRENT_LIST_DIR}/src/pico_audio/audio_utils.S>

)

## We need the arduino headers to be able to compile
target_include_directories(rp2040-i2s 
  PUBLIC
    "src"
  PRIVATE
    "src/arduino-ext"
)

target_link_libraries(rp2040-i2s 
#  pico_stdio_usb 
#  pico_stdlib 
  pico_sync
  hardware_dma
  hardware_pio
  hardware_irq
  hardware_clocks
)

