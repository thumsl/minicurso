#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <stdbool.h>
#include "linmath.h"
#include "shader.h"

typedef struct transformationMatrices {
	mat4x4 rotate;
	mat4x4 translate;
	mat4x4 scale;
	mat4x4 transform;
} transformationMatrices;

typedef struct mesh {
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	GLuint textureID;
	unsigned int vertexCount;
	unsigned int indexCount;
	transformationMatrices matrices;
} mesh;

static void mesh_init(mesh *model);
static void mesh_loadToVao(mesh *model, float *vertices, unsigned int *indices);
static void mesh_loadTexture(mesh *model, const char *texturePath);

mesh* mesh_createFromArrays(float *vertices, unsigned int *indices, 
	unsigned int vertexCount, unsigned int indexCount, const char *texturePath);

void mesh_draw(mesh *model, shader *S);

void mesh_translate(mesh *model, float x, float y, float z);
void mesh_rotate(mesh *model, bool x, bool y, bool z, float angle);
void mesh_scale(mesh *model, float x, float y, float z);

void mesh_updateTransformationMatrix(mesh *model);

// mesh* mesh_createFromFile(nomeDoArquivo.obj);

#endif // MESH_H