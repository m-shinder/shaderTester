#include <gtk-3.0/gtk/vim-gtk.h> // just copy of /usr/include/gtk-3.0/gtk/gtk.h for vim to correct autocompletion
#include <epoxy/gl.h>

#include "double-texture.h"

void on_glarea_realize(GtkGLArea* area, RenderData* renderData)
{
	return;
}

gboolean on_glarea_render(GtkGLArea* area, GdkGLContext* context, RenderData* renderData)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	return FALSE;
}
