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
  // do not add more sensors then are supported
  if (sensorCount < MONSENS_MAX_SENSORS) {
    sensors[sensorCount++] = &sensor;
    sensor.init();
  }
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
      if (reading < 0) {
        write('-');
      }
      writeInt(reading / 100);
      write('.');
      if (reading < 10 && reading > -10) {
        write('0');
      }
      writeInt(reading % 100);
      writeProgMem(MonSens_EOL);
      return;
    }
  }

  // when no sensor supports the input, print usage instructions instead
  writeProgMem(MonSens_Usage);
  for (uint8_t i = 0; i < sensorCount; ++i) {
    writeProgMem(sensors[i]->getUsage());
    writeProgMem(MonSens_EOL);
  }
}

/**
 * Write PROGMEM to the MCUs interface.
 */
void IMonSens_Communicator::writeProgMem(const char* line) {
  uint8_t i;
  char c;
  for (i = 0, c = 1; c; ++i) {
    c = pgm_read_byte_near(line + i);
    write(c);
  }
}

/**
 * Write integer to the MCUs interface.
 */
void IMonSens_Communicator::writeInt(const int16_t reading) {
  // convert to unsigned
  uint16_t n = (reading < 0) ? - (unsigned) reading : reading;
  uint16_t n10 = 10 * n;
  // make this the same order of magnitude as MAX_INT for your integer type
  uint16_t digit = 10000;

  if (0 == n) {
    write('0' + 0);
  } else {
    // reduce size of digit to match the magnitude of given reading
    while (digit > n10) {
      digit /= 10;
    }
    // write digits until we reach floor(1 / 10) = 0 (int division rounds down)
    while (digit /= 10) {
      write('0' + (n / digit) % 10);
    }
  }
}

