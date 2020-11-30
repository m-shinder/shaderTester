#include <gtk-3.0/gtk/vim-gtk.h> // just copy of /usr/include/gtk-3.0/gtk/gtk.h for vim to correct autocompletion
#ifndef __DOUBLE_TEXTURE_H
#define __DOUBLE_TEXTURE_H
typedef struct	render_data_struct
{
	int			VAO;
	int			VBO;
	int			EBO;
	int			shaderProgram;
}				RenderData;

gboolean on_glarea_render(GtkGLArea* area, GdkGLContext* context, RenderData* renderData);
void on_glarea_realize(GtkGLArea* area, RenderData* renderData);
void on_mainWindow_destroy();
void on_optionsCheckbox_toggled(GtkWidget* checkbox, GtkWidget* formHandler);
void on_recompileButton_clicked(GtkWidget* button, RenderData renderData);
#endif
