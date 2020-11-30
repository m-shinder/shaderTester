#include "double-texture.h"

void on_mainWindow_destroy()
{
	gtk_main_quit();
}

void on_optionsCheckbox_toggled(GtkWidget* checkbox, RenderOptions* renderOptions)
{
	if(g_strcmp0(gtk_widget_get_name(checkbox), "magB" ) == 0 )
		renderOptions->minBilinear = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox) );
	if(g_strcmp0(gtk_widget_get_name(checkbox), "minB" ) == 0 )
		renderOptions->minBilinear = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox) );
}

void on_recompileButton_clicked(GtkWidget* button, void* optionsAndData)
{
	return;
}

void on_texture_fileset(GtkWidget* filechooser, RenderOptions* renderOptions)
{
	if(g_strcmp0(gtk_widget_get_name(filechooser), "firstT" ) == 0 )
	{
		g_free(renderOptions->firstTexturePath);
		renderOptions->firstTexturePath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooser) );
	}
	if(g_strcmp0(gtk_widget_get_name(filechooser), "secondT" ) == 0 )
	{
		g_free(renderOptions->secondTexturePath);
		renderOptions->secondTexturePath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooser) );
	}
}

void on_vertexSSB_changed(GtkTextBuffer* buffer, RenderOptions *renderOptions)
{
	GtkTextIter start, end;
	g_free(renderOptions->vertexShaderSource);
	gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
	gtk_text_buffer_get_iter_at_offset(buffer, &end, -1);
	renderOptions->vertexShaderSource = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	//g_print(renderOptions->vertexShaderSource);
}

void on_fragmentSSB_changed(GtkTextBuffer* buffer, RenderOptions *renderOptions)
{
	GtkTextIter start, end;
	g_free(renderOptions->fragmentShaderSource);
	gtk_text_buffer_get_iter_at_offset(buffer, &start, 0);
	gtk_text_buffer_get_iter_at_offset(buffer, &end, -1);
	renderOptions->fragmentShaderSource = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	//g_print(renderOptions->fragmentShaderSource);
}
