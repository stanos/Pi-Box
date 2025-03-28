// Include system modules;
#include <wiringPi.h>

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

// Include local modules;
#include "gpio.h"
#include "../Config.h"

// Function that turns the status_led on and off to show that the program is running;
void* program_run_blink(void* vargp) {
	int i = 0;
	while (i < 1) {
		// Set the status_led pin to HIGH/On;
		digitalWrite(status_led, HIGH);
		usleep(1000 * 1000);
		// Set the status_led pin to LOW/Off;
		digitalWrite(status_led, LOW);
		usleep(1000 * 1000);
	}
}

// This function in initiated from the main.c file to initialize the gpio pins specified in the Config.c file;
int init_gpio() {
	wiringPiSetupGpio();
	
	// 
	for (int relay = 0; relay < sizeof(relays) / sizeof(relays[0]); relay++) {
		pinMode(relays[relay], OUTPUT);
	}
	for (int led = 0; led < sizeof(leds) / sizeof(leds[0]); led++) {
		pinMode(leds[led], OUTPUT);
	}
	
	pinMode(status_led, OUTPUT);

	pinMode(start_button, INPUT);
	pullUpDnControl(start_button, PUD_UP);
	
	pinMode(end_button, INPUT);
	pullUpDnControl(end_button, PUD_UP);
}

int gpio_setup() {
	if (verbose) {		
		// Print the specified "Relay Pins";
		printf("Relay Pins:\n");
		for (int relay = 0; relay < sizeof(relays) / sizeof(relays[0]); relay++) {
			printf("%i, ", relays[relay]);
		}
		printf("\n\n");
		printf("Status Led:\n");
		printf("%i,\n", status_led);
		printf("\n");
		// Print the specified "Led Pins";
		printf("Led Pins:\n");
		for (int led = 0; led < sizeof(leds) / sizeof(leds[0]); led++) {
			printf("%i, ", leds[led]);
		}
		printf("\n\n");
	}
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

int gpio_get(int pin, int value) {
	if (digitalRead(pin) == value) {
		return 1;
	} else {
		return 0;
	}
}