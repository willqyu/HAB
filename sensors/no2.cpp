#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "../main.h"
#include "../misc.h"
#include "no2.h"

void initNO2() {
    adc_gpio_init(B4WE);
    adc_gpio_init(B4AE);

}

void readNO2(struct STATE *state) {
    adc_select_input(0);
    uint16_t workingVoltage = adc_read();
    adc_select_input(1);
    uint16_t auxillaryVoltage = adc_read();
    float convWV = workingVoltage * conversionFactor;
    float convAV = auxillaryVoltage * conversionFactor;
    state->NO2WE = convWV;
    state->NO2AE = convAV;
    //printf("> (0) NO2 | rWV : %u | rAV : %u | WV : %.3f | AV : %.3f\n", workingVoltage, auxillaryVoltage, convWV, convAV);
    
}
