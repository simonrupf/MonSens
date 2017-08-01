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

#include <MonSens_Si7021.h>

/**
 * Inject the configured Adafruit sensor.
 */
void MonSens_Si7021::setSi7021(Adafruit_Si7021 &si7021) {
  sensor = si7021;
}

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_Si7021::init() {
  if(!sensor.begin()) {
    Serial.println("Could not find a valid Si7021 sensor, check wiring!");
    while(1);
  }
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_Si7021::measure(const char* input) {
  if (strstr(input, "C") != NULL) {
    reading = sensor.readTemperature() * 100;
  } else if (strstr(input, "RH") != NULL) {
    reading = sensor.readHumidity() * 100;
  } else {
    return false;
  }
  return true;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
const char* MonSens_Si7021::getUsage() {
  return MonSens_Si7021_Usage;
}

