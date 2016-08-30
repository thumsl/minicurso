#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "mesh.h"

static void mesh_loadToVao(mesh *model, float *vertices, unsigned int *indices) {
	glBindVertexArray(model->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
	glBufferData(GL_ARRAY_BUFFER, model->vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0); // <===
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

static void mesh_init(mesh *model) {
	glGenVertexArrays(1, &(model->VAO));

	glGenBuffers(1, &(model->VBO));
	glGenBuffers(1, &(model->IBO));

	glGenTextures(1, &(model->textureID));
}

static void mesh_loadTexture(mesh *model, const char *texturePath) {
	SDL_Surface *texture = IMG_Load(texturePath);

	if (texture == NULL) {
		fprintf(stderr, "Error: failed to load texture %s.\n%s\n", texturePath, IMG_GetError());
		return;
	}

	glBindTexture(GL_TEXTURE_2D, model->textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGB, 
		GL_UNSIGNED_BYTE, texture->pixels);

	SDL_FreeSurface(texture);
}

mesh* mesh_createFromArrays(float *vertices, unsigned int *indices, 
	unsigned int vertexCount, unsigned int indexCount, const char *texturePath) {

	mesh *model = (mesh*)malloc(sizeof(mesh));

	model->vertexCount = vertexCount;
	model->indexCount = indexCount;

	mesh_init(model);

	mesh_loadToVao(model, vertices, indices);

	if (texturePath != NULL)
		mesh_loadTexture(model, texturePath);

	return model;
}

void mesh_draw(mesh *model) {
	glBindVertexArray(model->VAO);
	glBindTexture(GL_TEXTURE_2D, model->textureID);
	glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
}