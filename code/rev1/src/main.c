#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "gpio/gpio.h"
#include "window.h"
#include "Config.h"

void* random_relay_mode(int delay) {
	if (verbose) {
		printf("Random Relay!\nDelay: %i\n\n", delay);
	}
	int z = 0;
	while (z < 1) {
		int value = rand() % ((sizeof(relays) / sizeof(relays[0])) + 0) + 0;
		if (verbose) {
			printf("Relay: %i\n", value);
		}
		gpio_set(relays[value], 0);
		if (delay == NULL) {
			usleep(rand() % (1000 - 50 + 1) + 100 * 1000);
		} else {
			usleep(delay * 1000);
		}
		gpio_set(relays[value], 1);
	}
}

void* random_led_mode(int delay) {
	if (verbose) {
		printf("Random Led!\nDelay: %i\n\n", delay);
	}
	int z = 0;
	while (z < 1) {
		int value = rand() % ((sizeof(leds) / sizeof(leds[0])) + 0) + 0;
		if (verbose) {
			printf("Led: %i\n", value);
		}
		gpio_set(leds[value], 0);
		if (delay == NULL) {
			usleep(rand() % (1000 - 50 + 1) + 100 * 1000);
		} else {
			usleep(delay * 1000);
		}
		gpio_set(leds[value], 1);
	}
}

int main(int argc, char **argv)
{
	int arg = 1;
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
		if (strcmp(argv[1], (char *)"-v") == 0) {
			verbose = true;
			argv[1] = NULL;
			arg = 2;
		}
		gpio_setup();
		if (argc > arg) {
			if (strcmp(argv[arg], (char *)"random-led") == 0){
				// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
				printf("Random Led Mode!\n");
				pthread_create(&random_leds, NULL, (void *)random_led_mode(250), NULL);
				pthread_create(&random_leds, NULL, (void *)random_led_mode(250), NULL);
				pthread_join(random_leds, 0);
			} else if (strcmp(argv[arg], (char *)"random-relay") == 0){
				// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
				printf("Random Relay Mode!\n");
				pthread_create(&random_relays, NULL, (void *)random_relay_mode(500), NULL);
				pthread_create(&random_relays, NULL, (void *)random_relay_mode(500), NULL);
				pthread_join(random_relays, 0);
			} else if (strcmp(argv[arg], (char *)"random-all") == 0){
				int delay = 500;
				if (argv[arg+1] == NULL) {
					delay = NULL;
				} else {
					delay = atoi(argv[arg+1]);
				}
				// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
				printf("Random Mode All!\nDelay: %i\n\n", delay);
				pthread_create(&random_relays, NULL, (void *)random_relay_mode(delay), NULL);
				pthread_create(&random_leds, NULL, (void *)random_led_mode(delay), NULL);
			} else if (strcmp(argv[arg], (char *)"test-cycle") == 0){
				// If given argument is equal to "test-cycle" then cycle through all pins specified in the Config.c file;
				printf("Test Cycle:\ncycling thru all pins!\n");
			} else {
				// If given argument is equal to anything else give an error that the argument given is not a valid argument;
				printf("%s is not a valid option!!\n", argv[1]);
			}
		} else {
			pthread_create(&main_program, NULL, (void *)init_window(argc, argv), NULL);
		}
		
	} else {
		// Check for args given; if not given, Create the window
		pthread_create(&main_program, NULL, (void *)init_window(argc, argv), NULL);
	}
}
