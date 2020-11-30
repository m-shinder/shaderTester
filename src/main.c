#include <gtk-3.0/gtk/vim-gtk.h> // just copy of /usr/include/gtk-3.0/gtk/gtk.h for vim to correct autocompletion
#include "double-texture.h"

int main(int argc, char** argv)
{
	GtkBuilder*		builder;
	GtkWidget*		window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "res/double-texture.ui", NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder, "doubleTextureWindow") );
	connect_all_signals(builder);

	g_object_unref(builder);

	gtk_widget_show(window);
	gtk_main();
	return 0;
}
