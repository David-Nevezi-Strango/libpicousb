/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
// #ifdef CYW43_WL_GPIO_LED_PIN
// #include "pico/cyw43_arch.h"
// #endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif
#include "hardware/structs/sio.h"
#include "hardware/structs/pads_bank0.h"
#include "hardware/structs/io_bank0.h"
#include "hardware/regs/io_bank0.h"   // IO_BANK0_GPIO2_CTRL_FUNCSEL_VALUE_SIOB_PROC_2
#include "hardware/gpio.h"
#include "hardware/resets.h"          // reset_block / unreset_block_wait

#define LED_PIN 2u

// #define GPIO_WATCH_PIN 2


void led_toggle() { sio_hw->gpio_togl = 1u << LED_PIN; }
bool repeating_timer_callback(__unused struct repeating_timer *t) {
    led_toggle();
    return true;
}

static struct repeating_timer timer;  

void set_irq(){
    // stdio_init_all(); //for serial printing, needs `screen` command to /dev/tty* also needs pico_enable_stdio_usb in cmake


    add_repeating_timer_ms(250, repeating_timer_callback, NULL, &timer);
}
void led_init_registers() {
    // Bring IO_BANK0 and PADS_BANK0 OUT of reset (and wait until done).
    // NOTE: reset_block_num() ASSERTS reset; unreset_block_num_wait_blocking() deasserts it.
    unreset_block_num_wait_blocking(6); //reset io and pads fpr routing gpio2 to sio
    unreset_block_num_wait_blocking(9);
    // mux GPIO2 to SIO — named value, not 0x5
    io_bank0_hw->io[LED_PIN].ctrl = _u(0x05);
    // clear ISO + OD atomically via the hw_clear alias — no read-modify-write race
    hw_clear_bits(&pads_bank0_hw->io[LED_PIN],
                  (_u(0x1) << 7) |  (_u(0x1) << 8));
    sio_hw->gpio_oe_set = 1u << LED_PIN;   // output enable
}


int main() {
    led_init_registers();
    set_irq();
    // hard_assert(rc == PICO_OK);
    sleep_ms(5000000);
    // while (true) {
        // led_toggle();
        // sleep_ms(LED_DELAY_MS);
        // led_toggle();
        // sleep_ms(LED_DELAY_MS);
    // }
}
