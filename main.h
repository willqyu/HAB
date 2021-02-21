

#define DEBUG 1

#define CORE_INIT_FLAG 69

#define LED_PIN 25
#define LOW_POWER_ALTITUDE 2000


static struct STATE
{
    // Current state of the payload
    // READING AND WRITING OPERATIONS MUST BE MUTEX'd TO REMAIN THREADSAFE
    long time;
    long secondsInDay;
    int Hours, Minutes, Seconds;
    float Longitude, Latitude;
    long Altitude;
    int Satellites;
} state;

void core_entry();
void blinkLED(struct STATE *s);
