#include <gtk/gtk.h>

#include "include/ui.h"

static void on_close(GtkWindow *window, gpointer data)
{
    (void)window;
    (void)data;

    g_application_quit(g_application_get_default());
}

static void activate(GtkApplication *app, gpointer data)
{
    (void)data;

    GtkWidget *window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "Bornomala Preview");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);

    g_signal_connect(window, "close-request", G_CALLBACK(on_close), NULL);

    gtk_window_present(GTK_WINDOW(window));
}

int ui_run(void)
{
    GtkApplication *app =
        gtk_application_new(
            "com.bornomala.preview",
            G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), 0, NULL);

    g_object_unref(app);

    return status;
}