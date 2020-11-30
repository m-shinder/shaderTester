#include "double-texture.h"

void on_mainWindow_destroy()
{
	gtk_main_quit();
}

void on_optionsCheckbox_toggled(GtkWidget* checkbox, GtkWidget* formHandler)
{
	g_object_set_data (
			G_OBJECT(formHandler),
			gtk_widget_get_name(GTK_WIDGET(checkbox)),
			gtk_toggle_button_get_active(checkbox)
			);
}

void on_recompileButton_clicked(GtkWidget* button, RenderData renderData)
{
	g_print("%d\n", g_object_get_data(button, "magB"));
	g_print("%d\n", g_object_get_data(button, "minB"));
}
