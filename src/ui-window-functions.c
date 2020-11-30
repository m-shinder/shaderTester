#include "double-texture.h"

void on_mainWindow_destroy()
{
	gtk_main_quit();
}

void on_optionsCheckbox_toggled(GtkWidget* checkbox, RenderOptions* renderOptions)
{
	if(g_strcmp0(gtk_widget_get_name(checkbox), "magB" ) == 0 )
		renderOptions->minBilinear = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox));
	if(g_strcmp0(gtk_widget_get_name(checkbox), "minB" ) == 0 )
		renderOptions->minBilinear = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox));
}

void on_recompileButton_clicked(GtkWidget* button, void* optionsAndData)
{
	return;
}
