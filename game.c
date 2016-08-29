
#include "engine.h"

int main() {
	SDL_Window *window = window_create("3D Game Engine", WIDTH, HEIGHT);

	float vertices[] = {
		-1, -1, 0,
		 1, -1, 0,
		 0,  1, 0 
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	SDL_GL_SwapWindow(window);

	SDL_Delay(2000);

	return 0;
}