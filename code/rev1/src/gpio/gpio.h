#include <wiringPi.h>

void* program_run_blink(void* vargp);
int init_gpio();
int cycle_relays(int value, int delay);
int cycle_leds(int value, int delay);
int gpio_set(int pin, int value);
