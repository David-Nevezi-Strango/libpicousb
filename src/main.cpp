/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "bsp.h"
// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
// #ifdef CYW43_WL_GPIO_LED_PIN
// #include "pico/cyw43_arch.h"
// #endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif


// #define GPIO_WATCH_PIN 2


int main() {
    led_init_registers();
    set_irq();
    // hard_assert(rc == PICO_OK);
    sleep_ms(5000000);
    while (true) {
        // led_toggle();
        // sleep_ms(LED_DELAY_MS);
        // led_toggle();
        // sleep_ms(LED_DELAY_MS);
    }
}
