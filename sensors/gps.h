#ifndef GPS_INCLUDED
#define GPS_INCLUDED

void initGPS(void);
void readGPS(struct STATE *state);
void writeFlightMode(struct STATE * state);

#endif