#ifndef BMP_INCLUDED
#define BMP_INCLUDED

void initBMP280();
int32_t compTemp(int32_t adc_T);
uint32_t compPress(int32_t adc_P);
void readCompValues();
int32_t readTemp();
uint32_t readPress();
#endif