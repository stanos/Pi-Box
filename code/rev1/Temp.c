#include <gtk/gtk.h>
#include <unistd.h>

#include "gpio/gpio.h"

#define APP_PREFIX "/home/stanos/pi-box/code/rev1"

int i;

G_MODULE_EXPORT void cycle_slow (GtkWidget *widget, gpointer data) {
  cycle_relays(1, 100);
  usleep(100 * 1000);
  cycle_relays(0, 100);
}

G_MODULE_EXPORT void cycle_fast (GtkWidget *widget, gpointer data) {
  cycle_relays(1, 10);
  usleep(10 * 1000);
  cycle_relays(0, 10);
}

G_MODULE_EXPORT void cycle_thru_relays() {
  int relays[8] = {21, 20, 16, 12, 1, 7, 8, 25};
  if(i < 1) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 1\n");
    i = 1;
  } else if(i == 1) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 2\n");
    i = 2;
  } else if(i == 2) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 3\n");
    i = 3;
  }else if(i == 3) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 4\n");
    i = 4;
  } else if(i == 2) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 5\n");
    i = 5;
  }else if(i == 1) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 6\n");
    i = 6;
  } else if(i == 2) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 7\n");
    i = 7;
  } else if(i == 2) {
    gpio_set(relays[i], 1);
    gpio_set(relays[i-1], 0);
    g_print ("cycle 8\n");
    i = 0;
  }
}

G_MODULE_EXPORT void quit(GtkWindow* window) {
  gtk_window_destroy(window);
}

static void activate (GtkApplication *app, gpointer user_data) {
  i = 0;
  GtkBuilder *build;
  GtkWidget *win;
  GtkWidget *cycle_f;
  GtkWidget *cycle_s;
  
  build = gtk_builder_new_from_file (APP_PREFIX "/ui/window.ui");
  win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
  gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
  g_object_unref(build);

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