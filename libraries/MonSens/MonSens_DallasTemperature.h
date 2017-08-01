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
 * @brief MonSens implementation of the Dallas 18B20 temperature sensor.
 *
 * The Dallas 18B20 temperature sensor allows multiple sensors to be connected
 * on a shared bus. These can be powered descretely on a separate wire or via
 * a "parasitic" mode over the serial pin, allowing 3 or 2 wire setups.
 */

#ifndef MONSENS_DALLASTEMPERATURE_H
#define MONSENS_DALLASTEMPERATURE_H

#include <MonSens.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char MonSens_DallasTemperature_Usage[] PROGMEM = {
  "C   - temperature in Celsius\r\nK   - temperature in Kelvin\r\n"
};

/**
 * MonSens implementation of the Dallas 18B20 temperature sensor.
 */
class MonSens_DallasTemperature: public IMonSens_Sensor {
  public:
    /**
     * Inject the configured Dallas temperature sensor bus.
     */
    void setDallas(DallasTemperature &dallas);

    /**
     * Set the index of the current sensor (optional), if more then one.
     */
    void setIndex(uint8_t index);

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
     * Index of the current sensor on the bus, defaults to 0
     */
    uint8_t sensorIndex = 0;

    /**
     * sensor interface
     */
    DallasTemperature sensor;
};

#endif

