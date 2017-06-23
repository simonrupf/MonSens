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

#ifndef MONSENS_H
#define MONSENS_H

#include <Arduino.h>

#ifndef MONSENS_MAX_SENSORS
#  define MONSENS_MAX_SENSORS 10
#endif
#ifndef MONSENS_MAX_MEASUREMENT_WIDTH
#  define MONSENS_MAX_MEASUREMENT_WIDTH 9
#endif

/**
 * Generic sensor interface, to be implemented by each MonSens sensor.
 */
class IMonSens_Sensor {
  public:
    /**
     * After it is registered in the communicator, the sensor gets initialized.
     */
    virtual void init() = 0;

    /**
     * Take a sensor reading, if the input is supported.
     */
    virtual bool measure(const char* input) = 0;

    /**
     * Returns the last sensor reading.
     */
    float getReading();

    /**
     * If no sensor supports the input value, usage instructions are collected.
     */
    virtual char* usage() = 0;

  protected:
    /**
     * Last measured sensor reading.
     */
    float reading = 0.0;
};

/**
 * Generic communication interface, to be implemented by each supported MCU.
 */
class IMonSens_Communicator {
  public:
    /**
     * Initialize the communicator, to be called in the MCUs setup routine.
     */
    virtual void init() = 0;

    /**
     * Register a sensor in the communicator.
     */
    void addSensor(IMonSens_Sensor &sensor);

    /**
     * Read inputs and respond to them, to be called in the MCUs loop routine.
     */
    virtual void communicate() = 0;

  protected:
    /**
     * List of sensors to handle.
     */
    IMonSens_Sensor* sensors[MONSENS_MAX_SENSORS];

    /**
     * Number of sensors to handle.
     */
    uint8_t sensorCount = 0;

    /**
     * Get the sensor measurement for a given input and write it to output
     */
    void askSensors(const char* input);

    /**
     * Write output to the MCUs interface, inserting a line break at the end.
     */
    virtual void println(const char* output);
};

#endif

