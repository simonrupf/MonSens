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
 * used to determine the delay amount needed to allow for the temperature
 * conversion to take place, 9-12
 */
#define MONSENS_DALLASTEMPERATURE_BITRESOLUTION 9

/**
 * Is parasite power mode used
 */
#define MONSENS_DALLASTEMPERATURE_PARASITE false

// Model IDs
#define DS18S20MODEL    0x10  // also DS1820
#define DS18B20MODEL    0x28
#define DS1822MODEL     0x22
#define DS1825MODEL     0x3B
#define DS28EA00MODEL   0x42

// OneWire commands
#define STARTCONVO      0x44  // Tells device to take a temperature reading and put it on the scratchpad
#define COPYSCRATCH     0x48  // Copy EEPROM
#define READSCRATCH     0xBE  // Read EEPROM
#define WRITESCRATCH    0x4E  // Write to EEPROM
#define RECALLSCRATCH   0xB8  // Reload from last known
#define READPOWERSUPPLY 0xB4  // Determine if device needs parasite power
#define ALARMSEARCH     0xEC  // Query bus for devices with an alarm condition

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

// Device resolution
#define TEMP_9_BIT      0x1F //  9 bit
#define TEMP_10_BIT     0x3F // 10 bit
#define TEMP_11_BIT     0x5F // 11 bit
#define TEMP_12_BIT     0x7F // 12 bit

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

