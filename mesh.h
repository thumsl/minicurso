#ifndef MESH_H
#define MESH_H

typedef struct mesh {
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	unsgined int vertexCount;
	unsgined int indexCount;
} mesh;

static void mesh_init(mesh *model);
static void mesh_loadToVao(mesh *model, float *vertices, unsgined int *indices);

mesh* mesh_createFromArrays(float *vertices, unsgined int *indices, 
	unsgined int vertexCount, unsgined int indexCount);

// mesh* mesh_createFromFile(nomeDoArquivo.obj);

#endif // MESH_H