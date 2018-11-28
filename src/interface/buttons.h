#ifndef BUTTONS_H
#define BUTTONS_H

#include <gtk/gtk.h>

void load_button(GtkButton *button, gpointer user_data);
void grayscale_button(GtkButton *button, gpointer user_data);
void binarize_button(GtkButton *button, gpointer user_data);
void deskew_button(GtkButton *button, gpointer user_data);
void segmentation_button(GtkButton *button, gpointer user_data);

#endif
