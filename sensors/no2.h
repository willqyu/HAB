#ifndef NO2_INCLUDED
#define NO2_INCLUDED

const float conversionFactor = 3.3f / (1 << 12);
void initNO2();
void readNO2(struct STATE *state);

#endif