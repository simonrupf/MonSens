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
 * @link <https://milesburton.com/Dallas_Temperature_Control_Library>
 * @brief MonSens implementation of the Dallas 18B20 temperature sensor.
 *
 * The Dallas 18B20 temperature sensor allows multiple sensors to be connected
 * on a shared bus. These can be powered descretely on a separate wire or via
 * a "parasitic" mode over the serial pin, allowing 3 or 2 wire setups.
 */

#include <MonSens_DallasTemperature.h>

/**
 * Inject the one-wire bus.
 */
void MonSens_DallasTemperature::setWire(OneWire* oneWire) {
  wire = oneWire;
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
    DeviceAddress deviceAddress;
    ScratchPad scratchPad;
    uint8_t depth = 0;

    wire->reset_search();
    while (depth <= sensorIndex && wire->search(deviceAddress)) {
      if (depth == sensorIndex && (wire->crc8(deviceAddress, 7) == deviceAddress[7])) {
        break;
      }
      ++depth;
    }
    wire->reset();
    wire->select(deviceAddress);
    wire->write(STARTCONVO, MONSENS_DALLASTEMPERATURE_PARASITE);
#if MONSENS_DALLASTEMPERATURE_BITRESOLUTION == 9
    delay(94);
#elif MONSENS_DALLASTEMPERATURE_BITRESOLUTION == 10
    delay(188);
#elif MONSENS_DALLASTEMPERATURE_BITRESOLUTION == 11
    delay(375);
#else
    delay(750);
#endif

    wire->reset();
    wire->select(deviceAddress);
    wire->write(READSCRATCH);

    // Read all registers in a simple loop
    // byte 0: temperature LSB
    // byte 1: temperature MSB
    // byte 2: high alarm temp
    // byte 3: low alarm temp
    // byte 4: DS18S20: store for crc
    //         DS18B20 & DS1822: configuration register
    // byte 5: internal use & crc
    // byte 6: DS18S20: COUNT_REMAIN
    //         DS18B20 & DS1822: store for crc
    // byte 7: DS18S20: COUNT_PER_C
    //         DS18B20 & DS1822: store for crc
    // byte 8: SCRATCHPAD_CRC
    for (uint8_t i = 0; i < 9; i++) {
      scratchPad[i] = wire->read();
    }
    wire->reset();

    if (
      (wire->crc8(scratchPad, 8) == scratchPad[SCRATCHPAD_CRC])
    ) {
      reading = (
        (((int16_t) scratchPad[TEMP_MSB]) << 11) |
        (((int16_t) scratchPad[TEMP_LSB]) << 3)
      ) * 100 / 128;
    } else {
      reading = -127;
    }
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

