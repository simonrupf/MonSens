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
 * @brief MonSens implementation of the ESP8266 internal voltage sensor.
 *
 * The ESP8266 can measure its internal voltage (around 2.7 - 3.1 V) when the
 * analog pin A0 is left unconnected.
 */

#include <MonSens_ESP8266_Vcc.h>

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_ESP8266_Vcc::init() {
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_ESP8266_Vcc::measure(const char* input) {
  if (strstr(input, "V") != NULL) {
    reading = (float) ESP.getVcc() / 1000.0;
    return true;
  }
  return false;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
const __FlashStringHelper* MonSens_ESP8266_Vcc::usage() {
  return F("V   - voltage at the ESP8266 chip");
}

