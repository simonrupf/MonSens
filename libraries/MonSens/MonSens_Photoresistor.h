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
 * @brief MonSens implementation of a simple light-sensitive resistor as sensor.
 *
 * Photoresistors, resistors that change their condictivity based on the light
 * in the environment, offer a simple solution to detect daylight or if a room
 * is in use or not, if the lights got turned off or similar.
 */

#ifndef MONSENS_PHOTORESISTOR_H
#define MONSENS_PHOTORESISTOR_H

#include <MonSens.h>

/**
 * MonSens implementation for a Photoresistor
 */
class MonSens_Photoresistor: public IMonSens_Sensor {
  public:
    /**
     * Set the analog pin to take measurements from.
     */
    void setAnalogPin(uint8_t pin);

    /**
     * After it is registered in the communicator, the sensor gets initialized.
     */
    void init();

    /**
     * Take a sensor reading, to be returned by the communicator.
     */
    bool measure(const char* input);

  #ifndef __DigiCDC_h__
    /**
     * If no sensor supports the input value, usage instructions are collected.
     */
    const __FlashStringHelper* usage();
  #endif

  private:
    /**
     * Analog pin the sensor is connected to
     */
    uint8_t sensorPin;
};

#endif

