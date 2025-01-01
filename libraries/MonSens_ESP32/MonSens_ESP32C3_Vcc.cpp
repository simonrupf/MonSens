/*
 * Copyright © 2025 Simon Rupf
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
 * @brief MonSens implementation of the ESP32C3 battery voltage sensor circuit.
 * @see https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/#check-the-battery-voltage
 *
 * The ESP32C3 can measure its battery voltage (around 2.7 - 4.2 V) when an
 * analog pin is connected in between a voltage divider formed by 2 x 220 kΩ
 * resistors, connected to battery Vcc & ground respectivelz.
 */

#include <MonSens_ESP32C3_Vcc.h>

inline void swap(uint32_t& a, uint32_t& b)
{
  register uint32_t temp = a;
  a = b;
  b = temp;
}

/**
 * Quickselect to pick median value
 *
 * @author Tony Hoare
 * @see Algorithm 65: find
 */
uint32_t quickselect(uint32_t arr[], int n)
{
  int low = 0;
  int high = n-1;
  int median = (low + high) / 2;
  int middle, ll, hh;

  while (true) {
    if (high <= low) /* One element only */
      return arr[median];

    if (high == low + 1) {  /* Two elements only */
      if (arr[low] > arr[high])
        swap(arr[low], arr[high]);
      return arr[median];
    }

    /* Find median of low, middle and high items; swap into position low */
    middle = (low + high) / 2;
    if (arr[middle] > arr[high]) swap(arr[middle], arr[high]);
    if (arr[low]    > arr[high]) swap(arr[low],    arr[high]);
    if (arr[middle] > arr[low])  swap(arr[middle], arr[low]);

    /* Swap low item (now in position middle) into position (low+1) */
    swap(arr[middle], arr[low+1]);

    /* Nibble from each end towards middle, swapping items when stuck */
    ll = low + 1;
    hh = high;
    while (true) {
      do ll++; while (arr[low] > arr[ll]);
      do hh--; while (arr[hh]  > arr[low]);

      if (hh < ll) break;

      swap(arr[ll], arr[hh]);
    }

    /* Swap middle item (in position low) back into correct position */
    swap(arr[low], arr[hh]);

    /* Re-set active partition */
    if (hh <= median) low = ll;
    if (hh >= median) high = hh - 1;
  }
}

/**
 * After it is registered in the communicator, the sensor gets initialized.
 */
void MonSens_ESP32C3_Vcc::init() {
  pinMode(MONSENS_ESP32C3_VCC_PIN, INPUT);
}

/**
 * Take a sensor reading, to be returned by the communicator.
 */
bool MonSens_ESP32C3_Vcc::measure(const char* input) {
  if (strstr(input, "V") != NULL) {
    uint32_t Vbatts[MONSENS_ESP32C3_VCC_ATTENUATION];
    for (int i = 0; i < MONSENS_ESP32C3_VCC_ATTENUATION; i++) {
      Vbatts[i] = analogReadMilliVolts(MONSENS_ESP32C3_VCC_PIN);
    }
    // ratio 1/2, mV to cV: 2 * Vbatt / 10 = Vbatt / (10 / 2)
    reading = quickselect(Vbatts, MONSENS_ESP32C3_VCC_ATTENUATION) / 5;
    return true;
  }
  return false;
}

/**
 * If no sensor supports the input value, usage instructions are collected.
 */
const char* MonSens_ESP32C3_Vcc::getUsage() {
  return MonSens_ESP32C3_Vcc_Usage;
}
