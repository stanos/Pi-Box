#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gpio/gpio.h"
#include "window.h"
#include "Config.h"

void* random_relay_mode() {
	int z = 0;
	while (z < 1) {
		int value = rand() % ((sizeof(relays) / sizeof(relays[0])) - 0) + 0;
		gpio_set(relays[value], 1);
		usleep(500 * 1000);
		gpio_set(relays[value], 0);
	}
}

void* random_led_mode() {
	int z = 0;
	while (z < 1) {
		int value = rand() % ((sizeof(leds) / sizeof(leds[0])) - 0) + 0;
		gpio_set(leds[value], 1);
		usleep(500 * 1000);
		gpio_set(leds[value], 0);
	}
}

int main(int argc, char **argv)
{
	// Initialize threads;
	pthread_t program_blink;
	pthread_t main_program;
	pthread_t random_leds;
	pthread_t random_relays;
	
	// Initialize GPIO First;
	init_gpio();

	// Make a thread to blink a led to show the program is running;
	pthread_create(&program_blink, NULL, (void *)program_run_blink, NULL);

	// Check if there are extra arguments given, if so:
	if (argc > 1) {
		if (strcmp(argv[1], (char *)"random-led") == 0){
			// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
			printf("Random Led Mode!\n");
			pthread_create(&random_leds, NULL, (void *)random_led_mode, NULL);
			pthread_create(&random_leds, NULL, (void *)random_led_mode, NULL);
			pthread_join(random_leds, 0);
		} else if (strcmp(argv[1], (char *)"random-relay") == 0){
			// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
			printf("Random Relay Mode!\n");
			pthread_create(&random_relays, NULL, (void *)random_relay_mode, NULL);
			pthread_create(&random_relays, NULL, (void *)random_relay_mode, NULL);
			pthread_join(random_relays, 0);
		} else if (strcmp(argv[1], (char *)"test-cycle") == 0){
			// If given argument is equal to "test-cycle" then cycle through all pins specified in the Config.c file;
			printf("Test Cycle:\ncycling thru all pins!\n");
		} else {
			// If given argument is equal to anything else give an error that the argument given is not a valid argument;
			printf("%s is not a valid option!", argv[1]);
		}

	} else {
		// Check for args given; if not given, Create the window
		pthread_create(&main_program, NULL, (void *)init_window(argc, argv), NULL);
	}
}
