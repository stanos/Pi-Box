#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gpio/gpio.h"
#include "window.h"
#include "Config.h"

void* random_led_mode() {
	int z = 0;
	while (z < 1) {
		int value = rand() % (4 - 0 + 1) + 0;
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

	// Initialize GPIO First;
	init_gpio();

	// Make a thread to blink a led to show the program is running;
	pthread_create(&program_blink, NULL, program_run_blink, NULL);

	// Check if there are extra arguments given, if so:
	if (argc > 1) {
		if (strcmp(argv[1], (char *)"random-led") == 0){
			// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
			printf("Random Led Mode!\n");
			pthread_create(&random_leds, NULL, random_led_mode, NULL);
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
