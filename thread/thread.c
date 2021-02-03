/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#define FLAG_VALUE 69
#define LED_PIN  25

void core1_entry() {
    multicore_fifo_push_blocking(FLAG_VALUE);

    uint32_t e = multicore_fifo_pop_blocking();

    if (e != FLAG_VALUE) {
        printf("Lmao u broke on 1\n");
    } else {
        printf("Nice. (1)\n");
    }

    while (1) {
        printf("oof\n");
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    
    }
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    printf("we vibin\n");

    multicore_launch_core1(core1_entry);
    uint32_t e = multicore_fifo_pop_blocking();

    if (e != FLAG_VALUE) {
        printf("0 sus");
    } else {
        multicore_fifo_push_blocking(FLAG_VALUE);
        printf("Nice. (0)");
    }
}
