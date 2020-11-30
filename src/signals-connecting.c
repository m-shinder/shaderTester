#include "double-texture.h"

int connect_glarea_signals(GtkGLArea* area, RenderData* renderData)
{
	g_signal_connect(
		GTK_WIDGET(area),
		"render",
		G_CALLBACK(on_glarea_render),
		renderData
	);
}

int connect_form_signals(GtkBuilder* builder, RenderOptions* renderOptions)
{
	// set every char* to NULL to avoid freeing of 'garbage' pointers
	renderOptions->vertexShaderSource = NULL;
	renderOptions->fragmentShaderSource = NULL;
	renderOptions->firstTexturePath = NULL;
	renderOptions->secondTexturePath = NULL;

	g_signal_connect(
		GTK_WIDGET(gtk_builder_get_object(builder, "magBilinearCheckbox") ),
		"toggled",
		G_CALLBACK(on_optionsCheckbox_toggled),
		renderOptions
	);

	g_signal_connect(
		GTK_WIDGET(gtk_builder_get_object(builder, "magBilinearCheckbox") ),
		"toggled",
		G_CALLBACK(on_optionsCheckbox_toggled),
		renderOptions
	);

	g_signal_connect(
		GTK_WIDGET(gtk_builder_get_object(builder, "firstTextureFileChooser") ),
		"file-set",
		G_CALLBACK(on_texture_fileset),
		renderOptions
	);

	g_signal_connect(
		GTK_WIDGET(gtk_builder_get_object(builder, "firstTextureFileChooser") ),
		"file-set",
		G_CALLBACK(on_texture_fileset),
		renderOptions
	);
}

int connect_all_signals(GtkBuilder* builder)
{
	void**	renderOptionsAndData = g_malloc(2*sizeof(void*));

	renderOptionsAndData[0] = g_malloc(sizeof(RenderOptions));
	renderOptionsAndData[1] = g_malloc(sizeof(RenderData));

	//it acually set every char* to NULL. Important side effect
	connect_form_signals(builder, renderOptionsAndData[0]);

	connect_glarea_signals(
		GTK_GL_AREA(gtk_builder_get_object(builder, "glarea") ),
		renderOptionsAndData[1]
	);
	g_signal_connect(
		GTK_WIDGET(gtk_builder_get_object(builder, "recompileButton") ),
		"clicked",
		G_CALLBACK(on_recompileButton_clicked),
		renderOptionsAndData
	);
	gtk_builder_connect_signals(builder, NULL);

}

