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
int16_t IMonSens_Sensor::getReading() {
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
 * Get the sensor measurement for a given input
 */
void IMonSens_Communicator::askSensors(const char* input) {
  // ignore empty input
  if (strlen(input) == 0) {
    return;
  }

  // check each sensor for support of the input,
  // returning the measurement if it does
  for (uint8_t i = 0; i < sensorCount; ++i) {
    if (sensors[i]->measure(input)) {
      int16_t reading = sensors[i]->getReading();
      if (reading < 0 && reading > -99) {
        write('-');
      }
      writeInt(reading / 100);
      write('.');
      if (reading < 10 && reading > -10) {
        write('0');
      }
      writeInt(((reading < 0) ? - (unsigned) reading : reading) % 100);
      write('\r');
      write('\n');
      return;
    }
  }

  // when no sensor supports the input, print usage instructions instead
  write('U');
  write('s');
  write('a');
  write('g');
  write('e');
  write(':');
  write('\r');
  write('\n');
  for (uint8_t i = 0; i < sensorCount; ++i) {
    const char* usage = sensors[i]->getUsage();
    for (uint8_t j = 0; j < MONSENS_MAX_USAGE_WIDTH; ++j) {
      char k = pgm_read_byte_near(usage + j);
      // write until null termination
      if (k) {
        write(k);
      } else {
        break;
      }
    }
    write('\r');
    write('\n');
  }
}

/**
 * Write integer to the MCUs interface.
 */
void IMonSens_Communicator::writeInt(const int16_t reading) {
  char measurement[MONSENS_MAX_MEASUREMENT_WIDTH];
  snprintf(measurement, MONSENS_MAX_MEASUREMENT_WIDTH, "%d", reading);
  for (uint8_t i = 0; measurement[i] && i < MONSENS_MAX_MEASUREMENT_WIDTH; ++i) {
    write(measurement[i]);
  }
}

