#ifndef BSP_H
#define BSP_H

#include "pico/stdlib.h"
#include "hardware/structs/sio.h"
#include "hardware/structs/pads_bank0.h"
#include "hardware/structs/io_bank0.h"
#include "hardware/regs/io_bank0.h"   // IO_BANK0_GPIO2_CTRL_FUNCSEL_VALUE_SIOB_PROC_2
#include "hardware/gpio.h"
#include "hardware/resets.h"          // reset_block / unreset_block_wait

static struct repeating_timer timer;  

void led_toggle();

void set_irq();

void led_init_registers();

bool repeating_timer_callback(__unused struct repeating_timer *t);
#endif //BSP_H