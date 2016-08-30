#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include "mesh.h"

static void mesh_loadToVao(mesh *model, float *vertices, unsigned int *indices) {
	glBindVertexArray(model->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
	glBufferData(GL_ARRAY_BUFFER, model->vertexCount * 5 * sizeof(float), vertices, 
		GL_STATIC_DRAW);

	// POSICAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0); // <===
	glEnableVertexAttribArray(0);

	// TEXTURA
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // <===
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

static void mesh_init(mesh *model) {
	glGenVertexArrays(1, &(model->VAO));

	glGenBuffers(1, &(model->VBO));
	glGenBuffers(1, &(model->IBO));

	glGenTextures(1, &(model->textureID));

	mat4x4_identity(model->matrices.rotate);
	mat4x4_identity(model->matrices.scale);
	mat4x4_identity(model->matrices.translate);
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

void mesh_draw(mesh *model, shader *S) {
	glUniformMatrix4fv(S->locTransform, 1, 0, (GLfloat*)model->matrices.transform);

	// DRAW
	glBindVertexArray(model->VAO);
	glBindTexture(GL_TEXTURE_2D, model->textureID);
	glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
}


void mesh_translate(mesh *model, float x, float y, float z) {
	mat4x4_translate(model->matrices.translate, x, y, z);
}

void mesh_rotate(mesh *model, bool x, bool y, bool z, float angle) {
	mat4x4_rotate(model->matrices.rotate, model->matrices.rotate, x, y, z, angle);
}

void mesh_scale(mesh *model, float x, float y, float z) {
	mat4x4_scale_aniso(model->matrices.scale, model->matrices.scale, x, y, z);
}

void mesh_updateTransformationMatrix(mesh *model) {
	// translate * rotacao * scale

	mat4x4_mul(model->matrices.transform, model->matrices.rotate, model->matrices.scale);
	mat4x4_mul(model->matrices.transform, model->matrices.translate, model->matrices.transform);
}