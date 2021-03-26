#ifndef BMP_INCLUDED
#define BMP_INCLUDED

static void readRegisters(uint8_t reg, uint8_t *buffer, uint16_t len);
void initBME280();
void readBME(struct STATE *s);
#endif