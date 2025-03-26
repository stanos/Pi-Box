#include <gtk/gtk.h>
#include <unistd.h>

#include "Config.h"
#include "gpio/gpio.h"

int loop_led;
int loop_relay;

G_MODULE_EXPORT void cycle_slow_led (GtkWidget *widget, gpointer data) {
  cycle_leds(1, 100);
  usleep(100 * 1000);
  cycle_leds(0, 100);
}

G_MODULE_EXPORT void cycle_slow_relay (GtkWidget *widget, gpointer data) {
  cycle_relays(1, 100);
  usleep(100 * 1000);
  cycle_relays(0, 100);
}

G_MODULE_EXPORT void cycle_fast_led (GtkWidget *widget, gpointer data) {
  cycle_leds(1, 10);
  usleep(10 * 1000);
  cycle_leds(0, 10);
}

G_MODULE_EXPORT void cycle_fast_relay (GtkWidget *widget, gpointer data) {
  cycle_relays(1, 10);
  usleep(10 * 1000);
  cycle_relays(0, 10);
}

G_MODULE_EXPORT void cycle_thru_relays() {
  if (loop_relay < 7) {
    loop_relay+=1;
    gpio_set(relays[loop_relay], 1);
  } else if (loop_relay > 7) {
    loop_relay = 0;
  }
}

G_MODULE_EXPORT void cycle_thru_leds() {
  gpio_set(21, 1);
  usleep(10 * 1000);
  gpio_set(21, 0);
}

G_MODULE_EXPORT void quit(GtkWindow* window) {
  exit(EXIT_SUCCESS);
}

static void activate (GtkApplication *app, gpointer user_data) {
  loop_relay = 0;
  loop_led = 0;
  GtkBuilder *build;
  GtkWidget *win;
  GtkWidget *cycle_f;
  GtkWidget *cycle_s;
  
  build = gtk_builder_new_from_file ("/home/stanos/pi-box/code/rev1/ui/pi-box.ui");
  win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  g_object_unref(build);
  
  gtk_window_fullscreen(GTK_WINDOW(win));

  gtk_window_present (GTK_WINDOW (win));
  
}

int init_window (int argc, char **argv) {
  GtkApplication *app;
  int status;
  
  app = gtk_application_new ("nl.sailingstanos.pi-box", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}