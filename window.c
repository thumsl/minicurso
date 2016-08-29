#include "window.h"

SDL_Window* window_create(const char *title, int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error: failed to initialize SDL.\n%s\n", SDL_GetError());
		return NULL;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window* window;
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
		height, SDL_WINDOW_OPENGL);

	if (window == NULL) {
		fprintf(stderr, "Error: failed to create a new window.\n%s\n", SDL_GetError());
		return NULL;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);

	return window;
}