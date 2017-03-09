#include <glib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

gsize length;
GdkPixbufLoader *loader;
GdkPixbuf *pixbuf;
GtkWidget *window;
GtkWidget *image;
guint8* buffer;

void on_destroy (GtkWidget *widget G_GNUC_UNUSED, gpointer user_data G_GNUC_UNUSED)
{
    gtk_main_quit ();
}
pthread_t th;

void* refresh_thread(void* x) {
	float t=0;
		for(t=0;;t+=0.1) {

				int i=0;
				for(i=0; i<640*480; i++) {
					buffer[i*3] = ((int)(i+10*(50*(sin(t)+1))))%255;
					buffer[i*3+1] = 0;
					buffer[i*3+2] = 0;
				}
			gtk_widget_queue_draw(GTK_WIDGET(image));
			usleep(20000);
		}
}

int main (int argc, char *argv[])
{
    buffer = (guint8*)malloc(640*480*3);

    gtk_init (&argc, &argv);

	int i=0;
	for(i=0; i<640*480; i++) {
		buffer[i*3] = i%255;
		buffer[i*3+1] = 0;
		buffer[i*3+2] = 0;
	}

	pixbuf = gdk_pixbuf_new_from_data (buffer, GDK_COLORSPACE_RGB, FALSE, 8, 640, 480, 640*3, NULL, NULL);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    image = gtk_image_new_from_pixbuf (pixbuf);
    gtk_container_add (GTK_CONTAINER (window), image);
    gtk_widget_show_all (GTK_WIDGET (window));
    g_signal_connect (window, "destroy", G_CALLBACK(on_destroy), NULL);

	pthread_create(&th, NULL, refresh_thread, NULL);

    gtk_main ();

    return 0;
}
