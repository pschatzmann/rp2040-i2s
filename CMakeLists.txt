cmake_minimum_required(VERSION 3.9)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
pico_sdk_init()

project(rp2040-i2s C CXX ASM)
file(GLOB_RECURSE I2S_H src/*.h)



add_library(rp2040-i2s  
    src/I2S.cpp src/pico_audio/audio.cpp 
    src/pico_audio/audio_utils.S 
    src/pico_audio_i2s/audio_i2s.c 
    src/pico_util_buffer/buffer.c )

target_link_libraries(rp2040-i2s PRIVATE
    pico_stdio_usb 
    pico_stdlib 
    pico_runtime
    pico_multicore 
    pico_util 
    pico_unique_id
    hardware_pwm 
    hardware_adc
    hardware_clocks
    hardware_spi
    hardware_i2c
    hardware_pio
    hardware_dma
)

target_include_directories(rp2040-i2s PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

install(TARGETS rp2040-i2s
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
