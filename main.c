#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/multicore.h"
#include "pico/mutex.h"

#include "main.h"
#include "misc.h"
#include "sensors/bmp.h"

//RUNTIME VARIABLES

uint64_t led_delay = 5000;
uint64_t last_led_time = 0;

static mutex_t mtx;

//MAIN CORE FUNCTIONS

int main() {

    //init serial
    setup_default_uart();
    debug("\n=== WM Pi Pico HAB Tracker V1.0 ===\n");

    debug("\n>>> Initialising modules ...\n\n");

    debug("> Initialise LED...");
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    debug(" Done\n");

    debug("> Initialise mutex...");
    mutex_init(&mtx);
    debug(" Done\n");

    debug("\n>>> Spooling thread... \n");
    multicore_launch_core1(core_entry);
    uint32_t r = multicore_fifo_pop_blocking();
    if (r != CORE_INIT_FLAG) {
        debug("<!> (0) Invalid parameter from Core 1!\n");
    } else {
        multicore_fifo_push_blocking(CORE_INIT_FLAG);
        debug("> (0) Core 0 initialised.\n");
    }

    while(1) {
        //mainloop
        
        //TODO:
        //send LoRa msg
        
    }
}

//THREADED FUNCTIONS

void core_entry() {

    multicore_fifo_push_blocking(CORE_INIT_FLAG);
    uint32_t r = multicore_fifo_pop_blocking();

    if (r != CORE_INIT_FLAG) {
        debug("<!> (1) Invalid parameter from Core 0!\n");
    } else {
        debug("> (1) Core 1 initialised.\n");
    }


    while(1) {
        //threadloop
        
        blinkLED(&state);
        //collect BMP220
        //collect N02 data
        //collect GPS data
    }
        
}

void blinkLED(struct STATE *s) {
    mutex_enter_blocking(&mtx);
    long alt = s->Altitude;
    uint64_t time = get_time() / 1000;
    mutex_exit(&mtx);
    
    if (alt < LOW_POWER_ALTITUDE) {
        led_delay = 500;
    } else {
        return;
    }
    if (time >= last_led_time + led_delay) {
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
        last_led_time = time;
    }
    
}



