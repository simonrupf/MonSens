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
 * @brief MonSens implementation for the DigiSpark microcontroller board.
 *
 * The DigiSpark MCU by DigiStump packages a small amount of memory and some
 * pins onto a circuit board that doubles as a USB plug.
 */

#include <MonSens_DigiSpark.h>

/**
 * Initialize the communicator, to be called in the MCUs setup routine.
 */
void MonSens_DigiSpark::init() {
  SerialUSB.begin();
}

/**
 * Read inputs and respond to them, to be called in the MCUs loop routine.
 */
void MonSens_DigiSpark::communicate() {
  // Check if a client has sent something
  if (SerialUSB.available()) {
    request[requestCounter] = SerialUSB.read();
    if (
      requestCounter > 1 ||
      request[requestCounter] == '\r' ||
      request[requestCounter] == '\n'
    ) {
      SerialUSB.delay(17); // wait for the client to be ready to read
      askSensors(request); // ask sensors for output and return it
      request = "";
      requestCounter = 0;
    } else {
      ++requestCounter;
      SerialUSB.delay(47); // wait for the shell to be ready to read
    }
  }
  SerialUSB.delay(3);
}

/**
 * Write output to the MCUs interface.
 */
void MonSens_DigiSpark::write(const char output) {
  SerialUSB.write(output);
}

