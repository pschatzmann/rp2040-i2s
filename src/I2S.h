/*
    I2S Master library for the Raspberry Pi Pico RP2040

    Copyright (c) 2021 Earle F. Philhower, III <earlephilhower@yahoo.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <Arduino.h>
#include "pico_audio_i2s/audio_i2s.h"

/**
 * @brief I2S for RP2040 Processors using the PIO: Only 16 bitsPerSample are allowed by the PIO code.  Only write, no read.
 * The default pins are: BCLK: GPIO26, LRCLK:GPIO27, DOUT: GPIO28. The LRCLK can not be defined separately and is BCLK+1!
 */
class I2SClass : public Stream {
public:
    I2SClass();

    /// Defines the BCLK pin
    bool setBCLK(pin_size_t pin);
    /// Defines the Data pin
    bool setDATA(pin_size_t pin);

    /// Starts the processing by defining the sample rate
    bool begin(long sampleRate);
    void end();

    /// Not supported
    virtual int available() override {
        return -1;
    }
    /// Not supported
    virtual int read() override {
        return -1;
    }
    /// Not supported
    virtual int peek() override {
        return -1;
    }

    virtual void flush() override;

    virtual size_t write(uint8_t) override;

    virtual size_t write(const uint8_t *buffer, size_t size) override;
    
    virtual int availableForWrite() override;

    /// Change the sample rate
    bool setFrequency(int newFreq);

    /// Write a single L:R sample to the I2S device.  Blocking until write succeeds
    size_t write(int16_t);
    
    /**
     * @brief Write up to size samples to the I2S device.  Non-blocking, will write
     * from 0...size samples and return that count.  Be sure your app handles
     * partial writes (i.e. by yield()ing and then retrying to write the
     * remaining data.
     * 
     * @param buffer 
     * @param lrsamples 
     * @return size_t 
     */
    size_t write(const void *buffer, size_t lrsamples);

    // Note that these callback are called from **INTERRUPT CONTEXT** and hence
    // must be both stored in IRAM and not perform anything that's not legal in
    // an interrupt
    //void onTransmit(void(*)(void)); -- Not yet implemented, need to edit pico-extra to get callback
    //void onReceive(void(*)(void)); -- no I2S input yet

private:
    pin_size_t _pinBCLK;
    pin_size_t _pinDOUT;
    int _bps;
    int _freq;
    bool _running;

    // Audio format/pool config
    audio_format_t _audio_format;
    audio_buffer_format_t _producer_format;
    audio_i2s_config_t _config;

    // We manage our own buffer pool here...
    audio_buffer_pool_t *_pool;
    audio_buffer_t *_curBuff;

    // Support for ::write(x) on 16b quantities
    uint32_t _writtenData;
    bool _writtenHalf;
};

extern I2SClass I2S;
