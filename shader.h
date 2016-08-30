#ifndef SHADER_H
#define SHADER_H

typedef struct shader {
	GLuint program;
	GLuint locTransform;
} shader;

shader* shader_createFromFile(const char *vertexShaderPath, 
	const char *fragmentShaderPath);

void shader_use(shader *S);

#endif // SHADER_H