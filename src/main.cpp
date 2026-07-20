/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
// #ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
// #endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif
#include "hardware/structs/sio.h"
#include "hardware/structs/pads_bank0.h"
#include "hardware/structs/io_bank0.h"
#include "hardware/regs/io_bank0.h"   // IO_BANK0_GPIO2_CTRL_FUNCSEL_VALUE_SIOB_PROC_2
#include "hardware/resets.h"          // reset_block / unreset_block_wait

#define LED_PIN 2u

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

void led_toggle() { sio_hw->gpio_togl = 1u << LED_PIN; }

int main() {
    led_init_registers();
    // hard_assert(rc == PICO_OK);
    while (true) {
        led_toggle();
        sleep_ms(LED_DELAY_MS);
        led_toggle();
        sleep_ms(LED_DELAY_MS);
    }
}

// #define REG_ACCESS(reg) (*((volatile unsigned long *) reg))
// #define SIO_BASE            0xD0000000
// #define PADS_BANK0_BASE     0x40038000
// #define IO_BANK0_BASE       0x40028000
// #define RESETS_BASE         0x40020000

// // #define PADS_BANK0                     REG_ACCESS(_u(0x00000200))
// // #define IO_BANK0                       REG_ACCESS(_u(0x00000040))

// #define RESETS_RESET                   REG_ACCESS(RESETS_BASE)
// #define RESETS_DONE                    REG_ACCESS(RESETS_BASE + _u(0x08))

// #define GPIO2_CTRL                    REG_ACCESS(IO_BANK0_BASE + _u(0x14))
// #define GPIO2_PADS                    REG_ACCESS(PADS_BANK0_BASE + _u(0x0c))

// #define GPIO_OE                        REG_ACCESS(SIO_BASE + _u(0x030))
// #define GPIO_OUT_SET                   REG_ACCESS(SIO_BASE + _u(0x018))
// #define GPIO_OUT_CLR                   REG_ACCESS(SIO_BASE + _u(0x020))
// #define GPIO_OUT                       REG_ACCESS(SIO_BASE + _u(0x010))

// void init_reg_access(){
//     long reset_val = (_u(0x1) << 6) | (_u(0x1) << 9); //deassert reset: IO_BANK0 (bit 6) and PADS_BANK0 (bit 9) on RP2350
//     RESETS_RESET &= ~(reset_val);
//     while((RESETS_DONE & reset_val) != reset_val){}
//     GPIO2_CTRL = _u(0x5);
//     GPIO2_PADS &= ~((_u(0x1) << 7) | (_u(0x1) << 8)); //clear OD and ISO (ISO defaults to 1 on RP2350, isolating the pad)
// }

// void delay(int limit){
//     volatile int count = 0;
//     while(count < limit){
//         count += 1;
//     }
// }

// int main(){
//     init_reg_access();
//     GPIO_OE |= _u(0x1) << 2; 
//     while(true){
//         GPIO_OUT ^= _u(0x1) << 2; 
//         delay(500000);
//     }
// }