#include <stdio.h>

#include <gtk/gtk.h>

#include "buttons.h"

void interface_start(void)
{
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "interface/interface.glade", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(builder, "image"));

    GObject *load_button = gtk_builder_get_object(builder, "load_button");
    g_signal_connect(load_button, "clicked", G_CALLBACK(load_image), image);

    GObject *quit_button = gtk_builder_get_object(builder, "quit_button");
    g_signal_connect(quit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(G_OBJECT(builder));
    gtk_widget_show(window);
    gtk_main();
}
