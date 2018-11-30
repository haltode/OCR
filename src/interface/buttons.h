#ifndef BUTTONS_H
#define BUTTONS_H

#include <gtk/gtk.h>

struct ocr_ui_data
{
    GtkWidget *image;
    GtkWidget *text;
};

void load_button(GtkButton *button, gpointer user_data);
void grayscale_button(GtkButton *button, gpointer user_data);
void binarize_button(GtkButton *button, gpointer user_data);
void deskew_button(GtkButton *button, gpointer user_data);
void noise_button(GtkButton *button, gpointer user_data);
void ocr_run_button(GtkButton *button, gpointer user_data);

#endif
