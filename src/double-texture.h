#include <gtk-3.0/gtk/vim-gtk.h> // just copy of /usr/include/gtk-3.0/gtk/gtk.h for vim to correct autocompletion
#ifndef __DOUBLE_TEXTURE_H
#define __DOUBLE_TEXTURE_H
typedef struct	reder_data_struct
{
	int			VAO;
	int			VBO;
	int			EBO;
	int			shaderProgram;
}				RenderData;

void on_glarea_realize(GtkGLArea* area, RenderData* renderData);
void on_main_window_destroy();
#endif
