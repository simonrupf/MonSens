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
 * BME280 sensor.
 *
 * The Bosch BME280 sensor offers humidity, barometric pressure and temperature
 * sensing in a single chip. Adafruit offers a breakout board to easily connect
 * the BME280 to an MCU: <https://www.adafruit.com/product/2652>
 *
 * There are other similar breakout boards that may be used with the Adafruit
 * libraries, as long as they offer either I2C or SPI interfaces. Using hardware
 * SPI is preferred, if your MCU supports it.
 */

#ifndef MONSENS_BME280_H
#define MONSENS_BME280_H

#include <MonSens.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// hardware SPI pins on NodeMCU v1, v2 & v3
//#define BME_SCK 14
//#define BME_MISO 12
//#define BME_MOSI 13
//#define BME_CS 15

#define SEALEVELPRESSURE_HPA (1013.25)

// use one of the below lines in your sketchbook to connect to the sensor
//Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

/**
 * MonSens implementation for the BME280 sensor
 */
class MonSens_BME280: public IMonSens_Sensor {
  public:
    /**
     * Inject the configured Adafruit sensor.
     */
    void setBme(Adafruit_BME280 &bme);

    /**
     * After it is registered in the communicator, the sensor gets initialized.
     */
    void init();

    /**
     * Check if this sensor supports a particular input value.
     */
    bool supports(const char* input);

    /**
     * Take a sensor reading, to be returned by the communicator.
     */
    char* measure(const char* input);

    /**
     * If no sensor supports the input value, usage instructions are collected.
     */
    char* usage();

  private:
    /**
     * sensor interface
     */
    Adafruit_BME280 sensor;

    /**
     * measured value as a formatted string
     */
    char measurement[9];
};

#endif

