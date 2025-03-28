// Include system modules;
#include <gtk/gtk.h>
#include <unistd.h>
#include <stdbool.h>

// Include local modules;
#include "Config.h"
#include "gpio/gpio.h"

// Initialize local variables;
int loop_led;
int loop_relay;

// Function ran when "Cycle Relays Slow" button is pressed;
G_MODULE_EXPORT void cycle_slow_led (GtkWidget *widget, gpointer data) {
  cycle_leds(1, 100);
  usleep(100 * 1000);
  cycle_leds(0, 100);
}

// Function ran when "Cycle Leds Slow" button is pressed;
G_MODULE_EXPORT void cycle_slow_relay (GtkWidget *widget, gpointer data) {
  cycle_relays(1, 100);
  usleep(100 * 1000);
  cycle_relays(0, 100);
}

// Function ran when "Cycle Leds Fast" button is pressed;
G_MODULE_EXPORT void cycle_fast_led (GtkWidget *widget, gpointer data) {
  cycle_leds(1, 10);
  usleep(10 * 1000);
  cycle_leds(0, 10);
}

// Function ran when "Cycle Relays Fast" button is pressed;
G_MODULE_EXPORT void cycle_fast_relay (GtkWidget *widget, gpointer data) {
  cycle_relays(1, 10);
  usleep(10 * 1000);
  cycle_relays(0, 10);
}

// Function ran when "Cycle Thru Relays" button is pressed;
G_MODULE_EXPORT void cycle_thru_relays() {
  if (loop_relay < 7) {
    loop_relay+=1;
    gpio_set(relays[loop_relay], 1);
  } else if (loop_relay > 7) {
    loop_relay = 0;
  }
}

// Function ran when "Cycle Thru Leds" button is pressed;
G_MODULE_EXPORT void cycle_random_leds() {
  int z = 0;
  while (z < 1) {
    int value = rand() % (4 - 0 + 1) + 0;
    gpio_set(leds[value], 1);
    usleep(500 * 1000);
    gpio_set(leds[value], 0);
  }
}

// Function ran when "Quit" button is pressed;
G_MODULE_EXPORT void quit(GtkWindow* window) {
  exit(EXIT_SUCCESS);
}

// This function creates the layout from the UI file located in the ui folder;
static void activate (GtkApplication *app, gpointer user_data) {
	// Initialize local variables;
  loop_relay = 0;
  loop_led = 0;
  GtkBuilder *build;
  GtkWidget *win;
  GtkWidget *cycle_f;
  GtkWidget *cycle_s;
  
	// Import ui file and load the layout;
  build = gtk_builder_new_from_file ("/home/stanos/pi-box/code/rev1/ui/pi-box.ui");
  win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  g_object_unref(build);
  
	// Fullscreen the newly created window;
  gtk_window_fullscreen(GTK_WINDOW(win));
  
	// Show the newly created window;
  gtk_window_present (GTK_WINDOW (win));
}

// This function is initiated from the main.c file to start the window creation process;
int init_window (int argc, char **argv) {
	// Initialize local variables;
  GtkApplication *app;
  int status;
  
	// Create the application;
  app = gtk_application_new ("nl.sailingstanos.pi-box", G_APPLICATION_DEFAULT_FLAGS);
	// Connect to the "activate" signal;
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	// Run the newly created application;
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  
	// Return status code;
  return status;
}
