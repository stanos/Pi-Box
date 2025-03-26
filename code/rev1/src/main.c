#include <pthread.h>

#include "gpio/gpio.h"
#include "window.h"
#include "Config.h"

int main(int argc, char **argv)
{
  // Initialize GPIO First
  init_gpio();

  // Make a thread to blink a led to show the program is running
  pthread_t program_blink;
  pthread_create(&program_blink, NULL, program_run_blink, NULL);

  // Create the window
  pthread_t main_program;
  void *main = (void*)init_window(argc, argv);
  pthread_create(&main_program, NULL, main, NULL);
  
}