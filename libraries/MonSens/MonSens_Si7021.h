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
 * @brief MonSens implementation for the Adafruit breakout board of the Silicon
 * Labs Si7021 sensor.
 *
 * The Silicon Labs Si7021 sensor offers relative humidity and temperature
 * sensing in a single chip. Adafruit offers a breakout board to easily connect
 * the Si7021 to an MCU: <https://www.adafruit.com/products/3251>
 *
 * There are other similar breakout boards that may be used with the Adafruit
 * libraries, as long as they offer an I²C interface.
 */

#ifndef MONSENS_SI7021_H
#define MONSENS_SI7021_H

#include <MonSens.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_Si7021.h>

const char MonSens_Si7021_Usage[] PROGMEM = {
  "C   - temperature in Celsius\r\nK   - temperature in Kelvin\r\nRH  - relative humidity in percents"
};

/**
 * MonSens implementation for the Si7021 sensor
 */
class MonSens_Si7021: public IMonSens_Sensor {
  public:
    /**
     * Inject the configured Adafruit sensor.
     */
    void setSi7021(Adafruit_Si7021 &si7021);

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
    /**
     * sensor interface
     */
    Adafruit_Si7021 sensor;
};

#endif

