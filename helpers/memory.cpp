#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "../main.h"
#include "../misc.h"
#include "memory.h"


void readChunk(const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
        if (i % 16 == 15)
            printf("\n");
        else
            printf(" ");
    }
}

void clearChunk(const uint32_t offset, size_t len) { 
    flash_range_erase(FLASH_TARGET_OFFSET + offset * FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE*len);

}

void writeChunk(const uint32_t offset, uint8_t data[], size_t len) {
    flash_range_program(FLASH_TARGET_OFFSET + offset * FLASH_SECTOR_SIZE, data, FLASH_SECTOR_SIZE*len);
}

void longToBytes(uint8_t buf[], long in) {
    buf[0] = in;
    buf[1] = in >> 8;
    buf[2] = in >> 16;
    buf[3] = in >> 24;
}

