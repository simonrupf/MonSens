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

#include <MonSens_ESP32C3_Vcc.h>

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_ESP32C3_Vcc::init() {
  pinMode(MONSENS_ESP32C3_VCC_PIN, INPUT);
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_ESP32C3_Vcc::measure(const char* input) {
  if (strstr(input, "V") != NULL) {
    uint32_t Vbatt = 0;
    for(int i = 0; i < MONSENS_ESP32C3_VCC_ATTENUATION; i++) {
      Vbatt = Vbatt + analogReadMilliVolts(MONSENS_ESP32C3_VCC_PIN);
    }
    // attenuation, ratio 1/2, mV to cV: 2 * Vbatt / Att. / 10 = Vbatt / (Att. * (10 / 2)) = Vbatt / (Att. * 5)
    reading = Vbatt / (MONSENS_ESP32C3_VCC_ATTENUATION * 5);
    return true;
  }
  return false;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
const char* MonSens_ESP32C3_Vcc::getUsage() {
  return MonSens_ESP32C3_Vcc_Usage;
}
