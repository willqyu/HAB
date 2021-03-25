#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/mutex.h"
#include "hardware/spi.h"
#include "hardware/watchdog.h"

#include "main.h"
#include "misc.h"
#include "lora.h"
#include "sensors/bmp.h"
#include "sensors/gps.h"
#include "helpers/repeater.h"



//RUNTIME VARIABLES
static Repeater LED_repeater(3000);
static Repeater BMP_repeater(500);
static Repeater GPS_repeater(0);

//MAIN CORE FUNCTIONS

int main() {

    //init usb output
    stdio_init_all();
    
    debug("\n=== WM Pi Pico HAB Tracker V1.0 ===\n");

    debug("\n>>> Initialising modules ...\n\n");

    debug("> Initialise LED... ");
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);
    LED_repeater.update_delay(50, 50, 50);
    debug("Done\n");

    debug("> Initialise SPI 0 & 1 @ 500kHz... ");
    spi_init(SPI_PORT_0, 500000);
    spi_init(SPI_PORT_1, 500000);
    //GPIO for SPI
    gpio_set_function(MISO_0, GPIO_FUNC_SPI);
    gpio_set_function(SCLK_0, GPIO_FUNC_SPI);
    gpio_set_function(MOSI_0, GPIO_FUNC_SPI);
    gpio_set_function(MISO_1, GPIO_FUNC_SPI);
    gpio_set_function(SCLK_1, GPIO_FUNC_SPI);
    gpio_set_function(MOSI_1, GPIO_FUNC_SPI);
    debug("Done\n");

    debug("> Initiailise I2C 0 & 1 @400kHz... ");
    i2c_init(I2C_PORT_0, 400*1000);
    gpio_set_function(SDA_0, GPIO_FUNC_I2C);
    gpio_set_function(SCL_0, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_0);
    gpio_pull_up(SCL_0);
    i2c_init(I2C_PORT_1, 400*1000);
    gpio_set_function(SDA_1, GPIO_FUNC_I2C);
    gpio_set_function(SCL_1, GPIO_FUNC_I2C);

    debug("Done\n");

    debug("> Initialise BMP280... ");
    initBME280();
    debug("Done\n");

    debug("> Initialise GPS... ");
    initGPS();
    debug("Done\n");
    
    debug("> Initialise mutex... ");
    mutex_init(&mtx);
    debug("Done\n");

    debug("> Enable watchdog... ");
    watchdog_enable(100, 0);
    debug("Done\n");

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
        
        watchdog_update();
        //TODO:
        check_LED(&state);
        check_BMP(&state);
        //collect N02 data
        check_GPS(&state);
        
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
        
        //TODO:
        //Send Lora message
        
    }
        
}

void check_LED(struct STATE *s) {
    mutex_enter_blocking(&mtx);
    long alt = s->Altitude;
    mutex_exit(&mtx);
    
    if (alt < LOW_POWER_ALTITUDE && LED_repeater.can_fire()) {
        gpio_put(LED_PIN, !gpio_get(LED_PIN));
    }
}

void check_BMP(struct STATE *s) {
    if (BMP_repeater.can_fire()) {
        int32_t temp = readTemp();
        uint32_t press = readPress();
        mutex_enter_blocking(&mtx);
        //printf("Temp = %.2fC | Press = %.2fPa \n", temp / 100.0, press / 256.0);
        s->Pressure = press;
        s->ExternalTemperature = temp;
        mutex_exit(&mtx);
    }
}

void check_GPS(struct STATE *s) {
    if (GPS_repeater.can_fire()) {
        readGPS(s);
    }
}



