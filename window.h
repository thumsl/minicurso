#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

SDL_Window* window_create(const char *title, int width, int height);

#endif // WINDOW_H