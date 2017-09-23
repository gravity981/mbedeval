/* mbed Microcontroller Library
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <events/mbed_events.h>
#include <mbed.h>
#include "neopixel.h"

using namespace neopixel;

static PixelArray pixelArray(SPI_PSELMOSI1);
DigitalOut led1(LED1, 1);
static EventQueue eventQueue(/* event count */ 16 * EVENTS_EVENT_SIZE);

void blinkCallback(void)
{
    led1 = !led1; /* Do blinky on LED1 while we're waiting for BLE events */
}

int main()
{
    eventQueue.call_every(500, blinkCallback);
    eventQueue.dispatch_forever();

    return 0;
}
