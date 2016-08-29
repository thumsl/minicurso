
#include "engine.h"

int main() {
	SDL_Window *window = window_create("3D Game Engine", WIDTH, HEIGHT);

	SDL_GL_SwapWindow(window);

	SDL_Delay(2000);

	return 0;
}