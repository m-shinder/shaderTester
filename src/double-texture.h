#include <gtk-3.0/gtk/vim-gtk.h> // just copy of /usr/include/gtk-3.0/gtk/gtk.h for vim to correct autocompletion
#ifndef __DOUBLE_TEXTURE_H
#define __DOUBLE_TEXTURE_H
typedef struct	render_data_struct
{
	int				VAO;
	int				VBO;
	int				EBO;
	int				shaderProgram;
	int				firstTexture;
	int				secondTexture;
	GtkGLArea		*area;
}				RenderData;

typedef struct	render_options_struct
{
	gboolean	magBilinear;
	gboolean	minBilinear;
	char*		vertexShaderSource;
	char*		fragmentShaderSource;
	char*		firstTexturePath;
	char*		secondTexturePath;

}				RenderOptions;

gboolean on_glarea_render(GtkGLArea* area, GdkGLContext* context, RenderData* renderData);
int connect_all_signals(GtkBuilder* builder);
void on_glarea_realize(GtkGLArea* area, RenderData* renderData);
void on_mainWindow_destroy();
void on_optionsCheckbox_toggled(GtkWidget* checkbox, RenderOptions* renderOptions);
void on_recompileButton_clicked(GtkWidget* button, void** optionsAndData);
void on_texture_fileset(GtkWidget* filechooser, RenderOptions* renderOptions);
void on_vertexSSB_changed(GtkTextBuffer* buffer, RenderOptions *renderOptions);
void on_fragmentSSB_changed(GtkTextBuffer* buffer, RenderOptions *renderOptions);
#endif
