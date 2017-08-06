/*
 * Copyright © 2017 Simon Rupf
 *
 * This file is part of MonSens.
 *
 * MonSens is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * MonSens is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with MonSens. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 * @author Simon Rupf <simon@rupf.net>
 * @link <https://milesburton.com/Dallas_Temperature_Control_Library>
 * @brief MonSens implementation of the Dallas 18B20 temperature sensor.
 *
 * The Dallas 18B20 temperature sensor allows multiple sensors to be connected
 * on a shared bus. These can be powered descretely on a separate wire or via
 * a "parasitic" mode over the serial pin, allowing 3 or 2 wire setups.
 */

#ifndef MONSENS_DALLASTEMPERATURE_H
#define MONSENS_DALLASTEMPERATURE_H

#include <MonSens.h>
#include <OneWire.h>

/**
 * Is parasite power mode used
 */
#define MONSENS_DALLASTEMPERATURE_PARASITE false

// OneWire commands
#define STARTCONVO      0x44  // Tells device to take a temperature reading and put it on the scratchpad
#define READSCRATCH     0xBE  // Read EEPROM

// Scratchpad locations
#define TEMP_LSB        0
#define TEMP_MSB        1
#define HIGH_ALARM_TEMP 2
#define LOW_ALARM_TEMP  3
#define CONFIGURATION   4
#define INTERNAL_BYTE   5
#define COUNT_REMAIN    6
#define COUNT_PER_C     7
#define SCRATCHPAD_CRC  8

const char MonSens_DallasTemperature_Usage[] PROGMEM = {
  "C   - temperature in Celsius\r\n"
};

/**
 * MonSens implementation of the Dallas 18B20 temperature sensor.
 */
class MonSens_DallasTemperature: public IMonSens_Sensor {
  public:
    /**
     * Inject the one-wire bus.
     */
    void setWire(OneWire* oneWire);

    /**
     * Set the index of the current sensor (optional), if more then one.
     */
    void setIndex(uint8_t index);

    /**
     * After it is registered in the communicator, the sensor gets initialized.
     */
    void init();

    /**
     * Take a sensor reading, to be returned by the communicator.
     */
    bool measure(const char* input);

    /**
     * If no sensor supports the input value, usage instructions are collected.
     */
    const char* getUsage();

  private:
    typedef uint8_t DeviceAddress[8];
    typedef uint8_t ScratchPad[9];

    /**
     * Index of the current sensor on the bus, defaults to 0
     */
    uint8_t sensorIndex = 0;

    /**
     * sensor interface
     */
    OneWire* wire;
};

#endif

