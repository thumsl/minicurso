#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

typedef struct mesh {
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	unsigned int vertexCount;
	unsigned int indexCount;
} mesh;

static void mesh_init(mesh *model);
static void mesh_loadToVao(mesh *model, float *vertices, unsigned int *indices);

mesh* mesh_createFromArrays(float *vertices, unsigned int *indices, 
	unsigned int vertexCount, unsigned int indexCount);

// mesh* mesh_createFromFile(nomeDoArquivo.obj);

#endif // MESH_H