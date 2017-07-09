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

#ifndef MONSENS_DIGISPARK_H
#define MONSENS_DIGISPARK_H

#define MONSENS_NO_USAGE

#include <MonSens.h>
#include <DigiCDC.h>

/**
 * MonSens implementation for the DigiSpark microcontroller board.
 */
class MonSens_DigiSpark: public IMonSens_Communicator {
  public:
    /**
     * Constructor
     */
    MonSens_DigiSpark() {}

    /**
     * Initialize the communicator, to be called in the MCUs setup routine.
     */
    void init();

    /**
     * Read inputs and respond to them, to be called in the MCUs loop routine.
     */
    void communicate();

  protected:
    /**
     * Write output to the MCUs interface.
     */
    void write(const char output);
};

#endif

