#include <wiringPi.h>

#include <unistd.h>
#include <stdio.h>
#include "gpio.h"

#include "../Config.h"

void* program_run_blink(void* vargp) {
    int i = 0;
    while (i < 1) {
        digitalWrite(status_led, HIGH);
        usleep(1000 * 1000);
        digitalWrite(status_led, LOW);
        usleep(1000 * 1000);
    }
}

int init_gpio() {
    wiringPiSetupGpio();
    
    printf("Relay Pins:\n");
    for (int relay = 0; relay < sizeof(relays) / sizeof(relays[0]); relay++) {
        printf("%i, ", relays[relay]);
    }
    printf("\n\n");

    printf("Led Pins:\n");
    for (int led = 0; led < sizeof(leds) / sizeof(leds[0]); led++) {
        printf("%i, ", leds[led]);
    }
    printf("\n");

    for (int relay = 0; relay < sizeof(relays) / sizeof(relays[0]); relay++) {
        pinMode(relays[relay], OUTPUT);
    }
    for (int led = 0; led < sizeof(leds) / sizeof(leds[0]); led++) {
        pinMode(leds[led], OUTPUT);
    }
    
    pinMode(start_button, INPUT);
    pullUpDnControl(start_button, PUD_UP);
    
    pinMode(end_button, INPUT);
    pullUpDnControl(end_button, PUD_UP);
}

int cycle_relays(int value, int delay) {
    if (value == 1) {
        for (int relay = 0; relay < sizeof(relays) / sizeof(relays[0]); relay++) {
            digitalWrite(relays[relay], HIGH);
            usleep(delay * 1000);
        }
    } else if (value == 0) {
        for (int relay = 0; relay < sizeof(relays) / sizeof(relays[0]); relay++) {
            digitalWrite(relays[relay], LOW);
            usleep(delay * 1000);
        }
    } else {
        printf("value needs to specified\n");
    }
    return 0;
}

int cycle_leds(int value, int delay) {
    if (value == 1) {
        for (int led = 0; led < sizeof(leds) / sizeof(leds[0]); led++) {
            digitalWrite(leds[led], HIGH);
            usleep(delay * 1000);
        }
    } else if (value == 0) {
        for (int led = 0; led < sizeof(leds) / sizeof(leds[0]); led++) {
            digitalWrite(leds[led], LOW);
            usleep(delay * 1000);
        }
    } else {
        printf("value needs to specified\n");
    }
    return 0;
}

int gpio_set(int pin, int value) {
    digitalWrite(pin, value);
}