#include <stdio.h>
#include "pico/stdlib.h"

#include "main.h"

void debug(const char * msg) {
    //Debugging
    if (DEBUG) {
        printf(msg);
    }
}



