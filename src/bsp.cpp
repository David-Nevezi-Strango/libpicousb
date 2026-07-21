#include "bsp.h"

#define LED_PIN 2u

void led_toggle() { sio_hw->gpio_togl = 1u << LED_PIN; }

bool repeating_timer_callback(__unused struct repeating_timer *t) {
    led_toggle();
    return true;
}


void set_irq(){
    // stdio_init_all(); //for serial printing, needs `screen` command to /dev/tty* also needs pico_enable_stdio_usb in cmake


    add_repeating_timer_ms(250, repeating_timer_callback, NULL, &timer);
}
void led_init_registers() {
    // Bring IO_BANK0 and PADS_BANK0 OUT of reset (and wait until done)..
    unreset_block_num_wait_blocking(6); 
    unreset_block_num_wait_blocking(9);
    //needed for routing gpio2 to sio
    // mux GPIO2 to SIO — named value, not 0x5
    io_bank0_hw->io[LED_PIN].ctrl = _u(0x05);
    // clear ISO + OD atomically via the hw_clear alias — no read-modify-write race
    hw_clear_bits(&pads_bank0_hw->io[LED_PIN],
                  (_u(0x1) << 7) |  (_u(0x1) << 8));
    sio_hw->gpio_oe_set = 1u << LED_PIN;   // output enable
}
