#pragma once

#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

template<typename T, typename... Args> void cleanup(T *t, Args&&... args);

template<> void cleanup<SDL_Window>(SDL_Window *win);
template<> void cleanup<SDL_Renderer>(SDL_Renderer *ren);
template<> void cleanup<SDL_Texture>(SDL_Texture *tex);
template<> void cleanup<SDL_Surface>(SDL_Surface *surf);
template<> void cleanup<SDL_Joystick>(SDL_Joystick *gameCtrlr);
