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

#ifndef MONSENS_BMP280_H
#define MONSENS_BMP280_H

#include <MonSens.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// hardware SPI pins on NodeMCU v1, v2 & v3
#ifndef BMP_SCK
#  define BMP_SCK 14
#endif
#ifndef BMP_MISO
#  define BMP_MISO 12
#endif
#ifndef BMP_MOSI
#  define BMP_MOSI 13
#endif
#ifndef BMP_CS
#  define BMP_CS 15
#endif

#ifndef SEALEVELPRESSURE_HPA
#  define SEALEVELPRESSURE_HPA (1013.25)
#endif

// use one of the below lines in your sketchbook to connect to the sensor
//Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK); // software SPI

const char MonSens_BMP280_Usage[] PROGMEM = {
  "C   - temperature in Celsius\r\nK   - temperature in Kelvin\r\nhPa - barometric pressure in hekto Pascal\r\nm   - altitude in meters above sealevel"
};

/**
 * MonSens implementation for the BMP280 sensor
 */
class MonSens_BMP280: public IMonSens_Sensor {
  public:
    /**
     * Inject the configured Adafruit sensor.
     */
    void setBmp(Adafruit_BMP280 &bmp);

    /**
     * After it is registered in the communicator, the sensor gets initialized.
     */
    void init();

    /**
     * Take a sensor reading, to be returned by the communicator.
     */
    bool measure(const char* input);

    /**
     * If no sensor supports the input value, usage instructions are collected.
     */
    const char* getUsage();

  private:
    /**
     * sensor interface
     */
    Adafruit_BMP280 sensor;
};

#endif

