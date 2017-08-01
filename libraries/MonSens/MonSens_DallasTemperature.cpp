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
 * @brief MonSens implementation of the Dallas 18B20 temperature sensor.
 *
 * The Dallas 18B20 temperature sensor allows multiple sensors to be connected
 * on a shared bus. These can be powered descretely on a separate wire or via
 * a "parasitic" mode over the serial pin, allowing 3 or 2 wire setups.
 */

#include <MonSens_DallasTemperature.h>

/**
 * Inject the configured Dallas temperature sensor bus.
 */
void MonSens_DallasTemperature::setDallas(DallasTemperature &dallas) {
  sensor = dallas;
}

/**
 * Set the index of the current sensor (optional), if more then one.
 */
void MonSens_DallasTemperature::setIndex(uint8_t index) {
  sensorIndex = index;
}

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_DallasTemperature::init() {
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_DallasTemperature::measure(const char* input) {
  if (strstr(input, "C") != NULL) {
    sensor.requestTemperaturesByIndex(sensorIndex);
    reading = sensor.getTempCByIndex(sensorIndex) * 100;
    return true;
  }
  return false;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
const char* MonSens_DallasTemperature::getUsage() {
  return MonSens_DallasTemperature_Usage;
}

