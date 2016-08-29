#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "shader.h"

int readFile(char** s, const char* filename) {
    struct stat st;
    int i;

    if(stat(filename, &st) == -1)
        return 0;

    *s = malloc(st.st_size+2);
    memset (*s, 0, st.st_size+2); // \0

    FILE *f;
    f = fopen(filename,"rb");
    fread(*s, 1, st.st_size, f);

    return 1;
}

shader* shader_createFromFile(const char *vertexShaderPath,	const char *fragmentShaderPath) {

	char *vertexSource, *fragmentSource;

	if (!readFile(&vertexSource, vertexShaderPath)) {
		fprintf(stderr, "Error: failed to open file '%s'\n", vertexShaderPath);
		return NULL;
	}

	if (!readFile(&fragmentSource, fragmentShaderPath)) {
		fprintf(stderr, "Error: failed to open file '%s'\n", fragmentShaderPath);
		return NULL;
	}

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char* const*)&vertexSource, NULL);
	glShaderSource(fragmentShader, 1, (const char* const*)&fragmentSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	GLint status1, status2;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status1);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status2);

	if (status1 != GL_TRUE) {
		char string[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, string);
		fprintf(stderr, "Compilation failed (Vertex Shader)\n%s\n", string);
	}

	if (status2 != GL_TRUE) {
		char string[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, string);
		fprintf(stderr, "Compilation failed (Fragment Shader)\n%s\n", string);
	}

	if (status1 != GL_TRUE || status2 != GL_TRUE)
		return NULL;

	shader *S = (shader*)malloc(sizeof(shader));
	S->program = glCreateProgram();

	glAttachShader(S->program, vertexShader);
	glAttachShader(S->program, fragmentShader);

	glLinkProgram(S->program);

	return S;
}

void shader_use(shader *S) {
	glUseProgram(S->program);
}
