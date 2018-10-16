#include "buttons.h"

void load_image(GtkButton* button, gpointer user_data)
{
    (void)(button);

    GtkWidget *image = GTK_WIDGET(user_data);
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

    GtkWindow *parent_window = GTK_WINDOW(gtk_widget_get_toplevel(image));
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open File",
                        parent_window,
                        action,
                        "Cancel",
                        GTK_RESPONSE_CANCEL,
                        "Open",
                        GTK_RESPONSE_ACCEPT,
                        NULL);
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_add_pixbuf_formats(filter);
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), filter);

    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        gchar *filename = gtk_file_chooser_get_filename(chooser);
        gtk_image_set_from_file(GTK_IMAGE(image), filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}