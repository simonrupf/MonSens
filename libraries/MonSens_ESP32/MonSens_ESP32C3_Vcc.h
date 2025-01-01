/*
 * Copyright © 2025 Simon Rupf
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
 * @brief MonSens implementation of the ESP32C3 battery voltage sensor circuit.
 * @see https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/#check-the-battery-voltage
 *
 * The ESP32C3 can measure its battery voltage (around 2.7 - 4.2 V) when an
 * analog pin is connected in between a voltage divider formed by 2 x 220 kΩ
 * resistors, connected to battery Vcc & ground respectivelz.
 */

#ifndef MONSENS_ESP32C3_VCC_H
#define MONSENS_ESP32C3_VCC_H

#include <MonSens.h>

// change if using a different pin, defaults to A0
#ifndef MONSENS_ESP32C3_VCC_PIN
#  define MONSENS_ESP32C3_VCC_PIN A0
#endif

// Attenuation factor: number of readings to take, gets averaged
#ifndef MONSENS_ESP32C3_VCC_ATTENUATION
#  define MONSENS_ESP32C3_VCC_ATTENUATION 16
#endif

const char MonSens_ESP32C3_Vcc_Usage[] PROGMEM = {
  "V   - voltage at the ESP32C3 chip\r\n"
};

/**
 * MonSens implementation of the ESP32C3 internal voltage sensor.
 */
class MonSens_ESP32C3_Vcc: public IMonSens_Sensor {
  public:
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
};

#endif
