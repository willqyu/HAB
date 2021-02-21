#include <stdio.h>
#include "pico/stdlib.h"

#include "main.h"

void debug(const char * msg) {
    //Debugging
    if (DEBUG) {
        printf(msg);
    }
}



uint64_t get_time(void) {
    // Returns result in us

    // Reading low latches the high value
    uint32_t lo = timer_hw->timelr;
    uint32_t hi = timer_hw->timehr;
    return ((uint64_t) hi << 32u) | lo;
}