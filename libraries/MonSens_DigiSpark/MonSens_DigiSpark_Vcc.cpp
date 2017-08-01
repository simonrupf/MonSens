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
 * @brief MonSens implementation of the ATtiny's internal voltage sensor.
 *
 * The DigiSpark can measure its internal voltage (around 5 V).
 */

#include <MonSens_DigiSpark_Vcc.h>

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_DigiSpark_Vcc::init() {
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_DigiSpark_Vcc::measure(const char* input) {
  if (strstr(input, "V") != NULL) {
    /*
     * Read 1.1V reference against AVcc
     * set the reference to Vcc and the measurement to the internal 1.1V reference
     * @link: <https://digistump.com/wiki/digispark/quickref>
     */
    #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
      ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
      ADMUX = _BV(MUX5) | _BV(MUX0);
    #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
      ADMUX = _BV(MUX3) | _BV(MUX2);
    #else
      ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    #endif

    delay(2); // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA, ADSC)); // measure

    uint8_t low  = ADCL; // read ADCL first - it locks ADCH  
    uint8_t high = ADCH; // unlock both
    uint16_t result = (high << 8) | low;

    reading = 112530 / result; // Calculate Vcc
    return true;
  }
  return false;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
const char* MonSens_DigiSpark_Vcc::getUsage() {
  return MonSens_DigiSpark_Vcc_Usage;
}

