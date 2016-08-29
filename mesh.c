#include <stdlib.h>
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
	// (QUANTIDADE DE BUFFERS, ARMAZENAMENTO DO PONTEIRO PRO BUFFER)
	glGenVertexArrays(1, &(model->VAO));
	glGenBuffers(1, &(model->VBO));
	glGenBuffers(1, &(model->IBO));
}

mesh* mesh_createFromArrays(float *vertices, unsigned int *indices, 
	unsigned int vertexCount, unsigned int indexCount) {

	mesh *model = (mesh*)malloc(sizeof(mesh));

	model->vertexCount = vertexCount;
	model->indexCount = indexCount;

	mesh_init(model);

	mesh_loadToVao(model, vertices, indices);

	return model;
}

void mesh_draw(mesh *model) {
	glBindVertexArray(model->VAO);
	glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
}