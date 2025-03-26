#include <wiringPi.h>

#include <unistd.h>
#include <stdio.h>
#include "gpio.h"

#include "../Config.h"

void* program_run_blink(void* vargp) {
    int i = 0;
    while (i < 1) {
        digitalWrite(leds[0], HIGH);
        usleep(1000 * 1000);
        digitalWrite(leds[0], LOW);
        usleep(1000 * 1000);
    }
}

int init_gpio() {
    wiringPiSetupGpio();
    
    for (int relay = 0; relay < sizeof(relays); relay++) {
        pinMode(relays[relay], OUTPUT);
    }
    for (int led = 0; led < sizeof(leds); led++) {
        pinMode(leds[led], OUTPUT);
    }
    
    pinMode(start_button, INPUT);
    pullUpDnControl(start_button, PUD_UP);
    
    pinMode(end_button, INPUT);
    pullUpDnControl(end_button, PUD_UP);
}

int cycle_relays(int value, int delay) {
    if (value == 1) {
        for (int relay = 0; relay < sizeof(relays); relay++) {
            digitalWrite(relays[relay], HIGH);
            usleep(delay * 1000);
        }
    } else if (value == 0) {
        for (int relay = 0; relay < sizeof(relays); relay++) {
            digitalWrite(relays[relay], LOW);
            usleep(delay * 1000);
        }
    } else {
        printf("value needs to specified");
    }
    return 0;
}

int gpio_set(int pin, int value) {
    digitalWrite(pin, value);
}