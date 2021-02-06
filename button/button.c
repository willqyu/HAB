#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#define DEBUG true
#define CORE_INIT_FLAG 69

#define BUTTON_PIN 15
#define LED_PIN 17

void debug(char* msg) {
    if (DEBUG) printf(msg);
}

void core1_entry() {

    // Init
    multicore_fifo_push_blocking(CORE_INIT_FLAG);
    uint32_t msg = multicore_fifo_pop_blocking();
    if (msg == CORE_INIT_FLAG) {
        printf(">>> Core 1 online\n");
    } else {
        printf("<!> Core 1 received error from core 0\n");
    }

    // Main thread loop
    while (1) {
        bool e;
        e = multicore_fifo_rvalid();
        if (e) {
            debug("(1) Data found in FIFO\n");
            int32_t header = multicore_fifo_pop_blocking();
            if (header == 1) { //case function with one argument and int32_t return;
                debug("(1) Parsing function\n");
                int32_t (*func)() = (int32_t(*)()) multicore_fifo_pop_blocking();
                int32_t arg = multicore_fifo_pop_blocking();
                int32_t result = (*func)(arg);
            } else {
                debug("(1) <!> Invalid header!\n");
            }
        }

    }

}

int32_t flash(int32_t delay) {
    gpio_put(LED_PIN, 1);
    sleep_ms(delay);
    gpio_put(LED_PIN, 0);
}

int main() {
    bool e;
    stdio_init_all();

    printf("\n>>> Online\n");

    // Init core
    multicore_launch_core1(core1_entry);
    uint32_t msg = multicore_fifo_pop_blocking();

    if (msg == CORE_INIT_FLAG) {
        debug(">>> Core 0 online\n");
        multicore_fifo_push_blocking(CORE_INIT_FLAG);
    } else {
        debug(">>> <!> Core 0 received error from core 1\n");
    }
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN);

    while (1) {
        if (gpio_get(BUTTON_PIN) == 1) {
            debug("(0) Check FIFO ready...\n");
            e = multicore_fifo_wready();
            if (e) {
                debug("(0) Push header, function and argument to FIFO\n");
                multicore_fifo_push_blocking(1);
                multicore_fifo_push_blocking((uintptr_t)&flash);
                multicore_fifo_push_blocking(500);
                sleep_ms(500);
            } else {
                debug("(0) <!> FIFO full!\n");
            }
            
        } else {
            
        }
    }
    
}