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
 * @brief MonSens implementation of the DigiSpark internal temperature sensor.
 *
 * The DigiSpark can measure the internal temperature inside the ATtiny85 MCU.
 */

#include <MonSens_DigiSpark_Temperature.h>

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_DigiSpark_Temperature::init() {
  analogReference(INTERNAL1V1);
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_DigiSpark_Temperature::measure(const char* input) {
  if (strstr(input, "C") != NULL) {
    reading = (analogRead(A0+15) - 273) * 100;
    return true;
  }
  return false;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
const char* MonSens_DigiSpark_Temperature::getUsage() {
  return MonSens_DigiSpark_Temperature_Usage;
}

