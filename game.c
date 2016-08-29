#include "engine.h"

int main() {
	SDL_Window *window = window_create("3D Game Engine", WIDTH, HEIGHT);
	if (window == NULL)
		return 1;

	if (!initOpenGL())
		return 1;

	shader* S = shader_createFromFile("shader.vert", "shader.frag");

	if (S == NULL)
		return 1;
	
	shader_use(S);

	float vertices[] = {
		-1, -1, 0,
		 1, -1, 0,
		 0,  1, 0 
	};

	unsigned int indices[] = {0, 1, 2};

	mesh *triangulo = mesh_createFromArrays(vertices, indices, 3, 3);

	bool running = true;
	SDL_Event event;

//	glClearColor(1.0f,1.0f,1.0f,1.0f);

	while (running) {
		/* INPUT HANDLING */
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					running = false;
			}
		}

		/* GAME LOGIC */

		/* RENDERING */
		glClear(GL_COLOR_BUFFER_BIT);
			// DESENHAMOS NOSSAS MESHES
			mesh_draw(triangulo);
		SDL_GL_SwapWindow(window);
	}

	return 0;
}