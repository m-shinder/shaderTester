#include <gtk-3.0/gtk/vim-gtk.h> // just copy of /usr/include/gtk-3.0/gtk/gtk.h for vim to correct autocompletion
#include <epoxy/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "double-texture.h"

int setVertices(RenderOptions* options, RenderData* data)
{

}

int load_texture(char* filename, int* texture)
{
	int width, height, nrChannels;
	g_print("t  %s\n", filename);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	if(nrChannels==3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	if(nrChannels==4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

int buildShaderProgram(const char* vSS, const char* fSS)
{
	int vertexShader;
	int fragmentShader;
	int shaderProgram;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vSS, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		g_print(infoLog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fSS, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		g_print(infoLog);
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

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

void on_recompileButton_clicked(GtkWidget* button, void** optionsAndData)
{
	RenderOptions*	options;
	RenderData*		data;

	options = optionsAndData[0];
	data = optionsAndData[1];
	load_texture(options->firstTexturePath, &(data->firstTexture));
	load_texture(options->secondTexturePath, &(data->secondTexture));

	data->shaderProgram = buildShaderProgram(options->vertexShaderSource, options->fragmentShaderSource);
	setVertices(options, data);
	g_print("%s\n======%s\n",options->vertexShaderSource, options->fragmentShaderSource);
}

