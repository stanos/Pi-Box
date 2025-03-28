#include <stdio.h>
#include <time.h>
#include <stdbool.h>

extern bool verbose = false;
extern int status_led = 26;

extern int relays[8] = {21, 20, 16, 12, 1, 7, 8, 25};
extern int leds[2] = {19, 13};

extern int start_button = 18;
extern int end_button = 17;
