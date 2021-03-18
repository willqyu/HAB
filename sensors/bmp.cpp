#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "../main.h"
#include "bmp.h"


int32_t t_fine;

//Compensation variables
//Temperature
uint16_t dig_T1;
int16_t dig_T2, dig_T3;
//Pressure
uint16_t dig_P1;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;


void initBMP280() {
    //GPIO CS
    gpio_init(CS_BMP);
    gpio_set_dir(CS_BMP, GPIO_OUT);
    gpio_put(CS_BMP, 1);
    
    readCompValues();

    //Configure chip sampling and power (x8)
    uint8_t data[2];
    data[0] = 0xF4 & 0x7F;
    data[1] = 0x27;
    gpio_put(CS_BMP, 0);
    spi_write_blocking(SPI_PORT_0, data, 2);
    gpio_put(CS_BMP, 1);
}

int32_t compTemp(int32_t adc_T) {
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t) dig_T1 << 1))) * ((int32_t) dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t) dig_T1)) * ((adc_T >> 4) - ((int32_t) dig_T1))) >> 12) * ((int32_t) dig_T3)) >> 14;

    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

uint32_t compPress(int32_t adc_P) {
    int64_t var1, var2, P;
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1*var1*(int64_t)dig_P6;
    var2 = var2 + ((var1*(int64_t)dig_P5) << 17); 
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;

    if (var1 == 0) {
        return 0;
    }

    P = 1048576 - adc_P;
    P = (((P << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (P >> 13) * (P >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * P) >> 19;
    P = ((P + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);

    return (uint32_t)P; 
}


void readCompValues() {
    uint8_t buffer[24], reg;

    reg = 0x88 | 0x80;
    gpio_put(CS_BMP, 0);
    spi_write_blocking(SPI_PORT_0, &reg, 1);
    spi_read_blocking(SPI_PORT_0, 0, buffer, 24);
    gpio_put(CS_BMP, 1);

    dig_T1 = buffer[0] | (buffer[1] << 8);
    dig_T2 = buffer[2] | (buffer[3] << 8);
    dig_T3 = buffer[4] | (buffer[5] << 8);
    dig_P1 = buffer[6] | (buffer[7] << 8);
    dig_P2 = buffer[8] | (buffer[9] << 8);
    dig_P3 = buffer[10] | (buffer[11] << 8);
    dig_P4 = buffer[12] | (buffer[13] << 8);
    dig_P5 = buffer[14] | (buffer[15] << 8);
    dig_P6 = buffer[16] | (buffer[17] << 8);
    dig_P7 = buffer[18] | (buffer[19] << 8);
    dig_P8 = buffer[20] | (buffer[21] << 8);
    dig_P9 = buffer[22] | (buffer[23] << 8);
}

int32_t readTemp() {
    int32_t temperature, rawTemp;
    uint8_t reg, buffer[3];
    reg = 0xFA | 0x80;
    gpio_put(CS_BMP, 0);
    spi_write_blocking(SPI_PORT_0, &reg, 1);
    spi_read_blocking(SPI_PORT_0, 0, buffer, 3);
    gpio_put(CS_BMP, 1);

    rawTemp = ((uint32_t) buffer[0] << 12) | ((uint32_t) buffer[1] << 4) | ((uint32_t) buffer[2] >> 4);
    temperature = compTemp(rawTemp);

    return temperature;
}

uint32_t readPress() {
    uint32_t pressure;
    int32_t rawPress;
    uint8_t reg, buffer[3];
    reg = 0xF7 | 0x80;
    gpio_put(CS_BMP, 0);
    spi_write_blocking(SPI_PORT_0, &reg, 1);
    spi_read_blocking(SPI_PORT_0, 0, buffer, 3);
    gpio_put(CS_BMP, 1);

    rawPress = ((uint32_t) buffer[0] << 12) | ((uint32_t) buffer[1] << 4) | ((uint32_t) buffer[2] >> 4);
    pressure = compPress(rawPress);
    return pressure;
}