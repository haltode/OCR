#include <string.h>

#include "../ocr.h"
#include "../preprocessing/preprocessing.h"
#include "../utils/constants.h"
#include "buttons.h"

char current_path_img[128];

void load_button(GtkButton *button, gpointer user_data)
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
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        gchar *filename = gtk_file_chooser_get_filename(chooser);

        gtk_image_set_from_file(GTK_IMAGE(image), filename);

        preprocessing(filename);

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void grayscale_button(GtkButton *button, gpointer user_data)
{
    (void)(button);
    GtkWidget *image = GTK_WIDGET(user_data);
    gtk_image_set_from_file(GTK_IMAGE(image), g_path_img_grayscale);
    strcpy(current_path_img, g_path_img_grayscale);
}

void binarize_button(GtkButton *button, gpointer user_data)
{
    (void)(button);
    GtkWidget *image = GTK_WIDGET(user_data);
    gtk_image_set_from_file(GTK_IMAGE(image), g_path_img_binarize);
    strcpy(current_path_img, g_path_img_binarize);
}

void deskew_button(GtkButton *button, gpointer user_data)
{
    (void)(button);
    GtkWidget *image = GTK_WIDGET(user_data);
    gtk_image_set_from_file(GTK_IMAGE(image), g_path_img_deskew);
    strcpy(current_path_img, g_path_img_deskew);
}

void noise_button(GtkButton *button, gpointer user_data)
{
    (void)(button);
    GtkWidget *image = GTK_WIDGET(user_data);
    gtk_image_set_from_file(GTK_IMAGE(image), g_path_img_noise_reduc);
    strcpy(current_path_img, g_path_img_noise_reduc);
}

void ocr_run_button(GtkButton *button, gpointer user_data)
{
    (void)(button);
    if (strcmp(current_path_img, g_path_img_binarize) != 0 &&
        strcmp(current_path_img, g_path_img_deskew) != 0 &&
        strcmp(current_path_img, g_path_img_noise_reduc) != 0)
        return;

    ocr_run(current_path_img);

    GtkWidget *image = GTK_WIDGET(user_data);
    gtk_image_set_from_file(GTK_IMAGE(image), g_path_img_segmentation);
}
