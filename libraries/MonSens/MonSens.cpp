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
 * @brief MonSens interfaces
 *
 * The MonSens interfaces to be implemented by each sensor type and MCU.
 */

#include <MonSens.h>

/**
 * Returns the last sensor reading.
 */
float IMonSens_Sensor::getReading() {
  return reading;
}

/**
 * Register a sensor in the communicator.
 */
void IMonSens_Communicator::addSensor(IMonSens_Sensor &sensor) {
  sensors[sensorCount++] = &sensor;
  sensor.init();
}

/**
 * Read inputs and respond to them, to be called in the MCUs loop routine.
 */
void IMonSens_Communicator::communicate() {
  const char* input = readln();

  // check each sensor for support of the input,
  // returning the measurement if it does
  for (int i = 0; i < sensorCount; ++i) {
    if (sensors[i]->measure(input)) {
      char measurement[MONSENS_MAX_MEASUREMENT_WIDTH];
      dtostrf(sensors[i]->getReading(), 0, 2, measurement);
      writeln(measurement);
      return;
    }
  }

  // ignore empty input, otherwise print usage
  if (strlen(input) > 0) {
    // when no sensor supports the input, print usage instructions instead
    writeln("Usage:");
    for (int j = 0; j < sensorCount; ++j) {
      writeln(sensors[j]->usage());
    }
  }
}

