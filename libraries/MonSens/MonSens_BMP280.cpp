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
 * @brief MonSens implementation for the Adafruit breakout board for the Bosch
 * BMP280 sensor.
 *
 * The Bosch BMP280 sensor offers barometric pressure and temperature sensing in
 * a single chip. Adafruit offers a breakout board to easily connect the BMP280
 * to an MCU: <https://www.adafruit.com/products/2651>
 *
 * There are other similar breakout boards that may be used with the Adafruit
 * libraries, as long as they offer either I2C or SPI interfaces. Using hardware
 * SPI is preferred, if your MCU supports it.
 */

#include <MonSens_BMP280.h>

/**
 * Inject the configured Adafruit sensor.
 */
void MonSens_BMP280::setBmp(Adafruit_BMP280 &bmp) {
  sensor = bmp;
}

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_BMP280::init() {
  if(!sensor.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while(1);
  }
  delay(100); // let the sensor boot up
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_BMP280::measure(const char* input) {
  if (strstr(input, "C") != NULL) {
    // read twice to avoid cached value
    sensor.readTemperature();
    reading = sensor.readTemperature();
  } else if (strstr(input, "K") != NULL) {
    // read twice to avoid cached value
    sensor.readTemperature();
    reading = sensor.readTemperature() + 273.15F;
  } else if (strstr(input, "hPa") != NULL) {
    // read twice to avoid cached value
    sensor.readPressure();
    reading = sensor.readPressure() / 100.0F;
  } else if (strstr(input, "m") != NULL) {
    // read twice to avoid cached value
    sensor.readAltitude(SEALEVELPRESSURE_HPA);
    reading = sensor.readAltitude(SEALEVELPRESSURE_HPA);
  } else {
    return false;
  }
  return true;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
char* MonSens_BMP280::usage() {
  return "C   - temperature in Celsius\r\nK   - temperature in Kelvin\r\nhPa - barometric pressure in hekto Pascal\r\nm   - altitude in meters above sealevel";
}

