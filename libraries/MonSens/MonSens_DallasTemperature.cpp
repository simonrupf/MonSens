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
    requestTemperaturesByIndex(sensorIndex);
    reading = getTempByIndex(sensorIndex);
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

/**
 * Is the given address valid
 */
bool MonSens_DallasTemperature::isValidAddress(const uint8_t* deviceAddress) {
  return (wire->crc8(deviceAddress, 7) == deviceAddress[7]);
}

/**
 * attempt to determine if the device at the given address is connected to the
 * bus also allows for updating the read scratchpad
 */
bool MonSens_DallasTemperature::isConnected(const uint8_t* deviceAddress, uint8_t* scratchPad) {
  bool b = readScratchPad(deviceAddress, scratchPad);
  return b && (wire->crc8(scratchPad, 8) == scratchPad[SCRATCHPAD_CRC]);
}

/**
 * Update the read scratchpad
 */
bool MonSens_DallasTemperature::readScratchPad(const uint8_t* deviceAddress, uint8_t* scratchPad) {
  // send the reset command and fail fast
  int8_t b = wire->reset();
  if (b == 0) return false;

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

  b = wire->reset();
  return (b == 1);
}

/**
 * sends command for one device to perform a temp conversion by index
 */
bool MonSens_DallasTemperature::requestTemperaturesByIndex(uint8_t deviceIndex) {
  DeviceAddress deviceAddress;
  getAddress(deviceAddress, deviceIndex);

  wire->reset();
  wire->select(deviceAddress);
  wire->write(STARTCONVO, parasite);

  blockTillConversionComplete(bitResolution);
  return true;
}

/**
 * finds an address at a given index on the bus
 * returns true if the device was found
 */
bool MonSens_DallasTemperature::getAddress(uint8_t* deviceAddress, uint8_t index) {
  uint8_t depth = 0;
  wire->reset_search();
  while (depth <= index && wire->search(deviceAddress)) {
    if (depth == index && isValidAddress(deviceAddress)) {
      return true;
    }
    ++depth;
  }
  return false;
}

/**
 * Fetch temperature for device index
 */
int16_t MonSens_DallasTemperature::getTempByIndex(uint8_t deviceIndex) {
  DeviceAddress deviceAddress;
  if (!getAddress(deviceAddress, deviceIndex)) {
      return -127;
  }

  ScratchPad scratchPad;
  if (isConnected(deviceAddress, scratchPad)) {
    int16_t fpTemperature =
      (((int16_t) scratchPad[TEMP_MSB]) << 11) |
      (((int16_t) scratchPad[TEMP_LSB]) << 3);
    return fpTemperature * 100 / 128;
  } else {
    return -127;
  }
}

/**
 * Continue to check if the IC has responded with a temperature
 */
void MonSens_DallasTemperature::blockTillConversionComplete(uint8_t bitResolution) {
  uint16_t delms;
  switch (bitResolution) {
    case 9:
      delms = 94;
    case 10:
      delms = 188;
    case 11:
      delms = 375;
    default:
      delms = 750;
  }
  if (!parasite){
    unsigned long now = millis();
    while(wire->read_bit() != 1 && (millis() - delms < now));
  } else {
    delay(delms);
  }
}

