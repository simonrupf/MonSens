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
  // Check if a client has connected
  if (SerialUSB.available()) {
    char request[4];
    for (uint8_t i = 0; i < 3 && request[i] != '\r' && request[i] != '\n'; ++i) {
      request[i] = SerialUSB.read();
      SerialUSB.delay(50); // wait for the shell to be ready to read
    }

    // ask sensors for output and return it
    askSensors(request);
  }

  SerialUSB.delay(3);
}


/**
 * Write output to the MCUs interface, inserting a line break at the end.
 */
void MonSens_DigiSpark::println(const char* output) {
  SerialUSB.println(output);
}

