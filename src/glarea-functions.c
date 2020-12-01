#include <gtk-3.0/gtk/vim-gtk.h> // just copy of /usr/include/gtk-3.0/gtk/gtk.h for vim to correct autocompletion
#include <epoxy/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "double-texture.h"

int setVertices(RenderOptions* options, RenderData* data)
{
	float vertices[] = {
	//	  X		 Y		Z		 R	   G	 B	   A		 S	   T
		-0.5f, -0.5f,  0.0f,	1.0f, 1.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.0f,	1.0f, 0.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		 0.5f,  0.5f,  0.0f,	0.0f, 1.0f, 1.0f, 1.0f,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,	1.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	printf("glerrV %d\n",glGetError());
	glGenVertexArrays(1, &(data->VAO));
	glBindVertexArray(data->VAO);

	glGenBuffers(1,&(data->VBO));
	glBindBuffer(GL_ARRAY_BUFFER, data->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &(data->EBO));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// TODO: make it depends on options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glUniform1i(glGetUniformLocation(data->shaderProgram,"Texture1"), 0);
	glUniform1i(glGetUniformLocation(data->shaderProgram,"Texture2"), 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	printf("glerrVE %d\n",glGetError());

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
	printf("glerr0 %d\n",glGetError());

	glUseProgram(renderData->shaderProgram);
	//printf("glerrM %d\n",glGetError());
	//glUniform1f(glGetUniformLocation(renderData->shaderProgram, "xOffset"), 0.0f);
	//printf("glerrm %d\n",glGetError());
	glActiveTexture(GL_TEXTURE0);
	printf("glerr1 %d\n",glGetError());
	glBindTexture(GL_TEXTURE_2D, renderData->firstTexture);
	printf("glerr2 %d\n",glGetError());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderData->secondTexture);
	printf("glerr3 %d\n",glGetError());
	glBindVertexArray(renderData->VAO);
	printf("glerr4 %d\n",glGetError());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderData->EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glFlush();

	printf("glerr5 %d\n",glGetError());
	g_print("render flushed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111\n");

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

