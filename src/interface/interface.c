#include <stdlib.h>

#include <gtk/gtk.h>

#include "buttons.h"

void interface_start(void)
{
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "src/interface/interface.glade", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
    GtkWidget *text = GTK_WIDGET(gtk_builder_get_object(builder, "text"));

    GObject *button;
    button = gtk_builder_get_object(builder, "load_button");
    g_signal_connect(button, "clicked", G_CALLBACK(load_button), image);

    button = gtk_builder_get_object(builder, "grayscale_button");
    g_signal_connect(button, "clicked", G_CALLBACK(grayscale_button), image);

    button = gtk_builder_get_object(builder, "binarize_button");
    g_signal_connect(button, "clicked", G_CALLBACK(binarize_button), image);

    button = gtk_builder_get_object(builder, "deskew_button");
    g_signal_connect(button, "clicked", G_CALLBACK(deskew_button), image);

    button = gtk_builder_get_object(builder, "noise_button");
    g_signal_connect(button, "clicked", G_CALLBACK(noise_button), image);

    struct ocr_ui_data *ocr_ui = malloc(sizeof(struct ocr_ui_data));
    ocr_ui->image = image;
    ocr_ui->text = text;
    button = gtk_builder_get_object(builder, "ocr_run_button");
    g_signal_connect(button, "clicked", G_CALLBACK(ocr_run_button), ocr_ui);

    button = gtk_builder_get_object(builder, "quit_button");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    gtk_main();

    free(ocr_ui);
}
