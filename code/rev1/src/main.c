#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "gpio/gpio.h"
#include "window.h"
#include "Config.h"

char* valid_commands[4] = {"random-all", "random-led", "random-relay", "-v"};

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
	bool command_given = false;
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
		for (int arg = 1; arg < argc; arg++) {
			if (strcmp(argv[arg], (char *)"-v") == 0) {
				verbose = true;
				printf("Verbose Mode!\n");
				
				gpio_setup();
			} else if (strcmp(argv[arg], (char *)"random-led") == 0 && command_given != true){
				// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
				printf("Random Led Mode!\n");
				command_given = true;
				if (strcmp(argv[arg+1], (char *)"-v") == 0) {
					verbose = true;
					printf("Verbose Mode!\n");
					
					gpio_setup();
				} else {
					printf("NON-Verbose Mode!\n");
				}
				pthread_create(&random_leds, NULL, (void *)random_led_mode(250), NULL);
				pthread_create(&random_leds, NULL, (void *)random_led_mode(250), NULL);
				pthread_join(random_leds, 0);
			} else if (strcmp(argv[arg], (char *)"random-relay") == 0 && command_given != true){
				// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
				printf("Random Relay Mode!\n");
				command_given = true;
				if (strcmp(argv[arg+1], (char *)"-v") == 0) {
					verbose = true;
					printf("Verbose Mode!\n");
					
					gpio_setup();
				} else {
					printf("NON-Verbose Mode!\n");
				}
				pthread_create(&random_relays, NULL, (void *)random_relay_mode(500), NULL);
				pthread_create(&random_relays, NULL, (void *)random_relay_mode(500), NULL);
				pthread_join(random_relays, 0);
			} else if (strcmp(argv[arg], (char *)"random-all") == 0 && command_given != true){
				
				int delay = 500;
				if (argv[arg+1] == NULL) {
					delay = NULL;
					if (strcmp(argv[arg+1], (char *)"-v") == 0) {
						verbose = true;
						printf("Verbose Mode!\n");
						
						gpio_setup();
					} else {
						printf("NON-Verbose Mode!\n");
					}
				} else {
					delay = atoi(argv[arg+1]);
				}
				// If given argument is equal to "random-led", then start the random_leds thread running the random_led_mode (AKA blink random leds continiously);
				printf("Random Mode All!\nDelay: %i\n\n", delay);
				command_given = true;
				
				pthread_create(&random_relays, NULL, (void *)random_relay_mode(delay), NULL);
				pthread_create(&random_leds, NULL, (void *)random_led_mode(delay), NULL);
				
				pthread_join(random_relays, 0);
				pthread_join(random_leds, 0);
			} else {
				for (int x = 0; x < (sizeof(valid_commands) / sizeof(valid_commands[0])); x++) {
					if (strcmp(argv[arg], valid_commands[x]) == 0) {
						printf("ERROR: 101");
					} 
				}
				// If given argument is equal to anything else give an error that the argument given is not a valid argument;
				printf("%s is not a valid option!!\n", argv[arg]);
				break;
			}
		} 
	} else {
		
		gpio_setup();
		// Check for args given; if not given, Create the window
		pthread_create(&main_program, NULL, (void *)init_window(argc, argv), NULL);
	}
}
