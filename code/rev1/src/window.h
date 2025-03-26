#ifndef WINDOW_H_
#define WINDOW_H_

#include <gtk/gtk.h>

int init_window(int argc, char **argv);
static void activate(GtkApplication* app, gpointer user_data);

#endif