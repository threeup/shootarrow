#pragma once

#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

void cleanup(SDL_Window *win);
void cleanup(SDL_Renderer *ren);
void cleanup(SDL_Texture *tex);
void cleanup(SDL_Surface *surf);
void cleanup(SDL_Joystick *gameCtrlr);


