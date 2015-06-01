
#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "cleanup.h"


void cleanup(SDL_Window *win){
	if (!win){
		return;
	}
	SDL_DestroyWindow(win);
}

void cleanup(SDL_Renderer *ren){
	if (!ren){
		return;
	}
	SDL_DestroyRenderer(ren);
}
void cleanup(SDL_Texture *tex){
	if (!tex){
		return;
	}
	SDL_DestroyTexture(tex);
}
void cleanup(SDL_Surface *surf){
	if (!surf){
		return;
	}
	SDL_FreeSurface(surf);
}
void cleanup(SDL_Joystick *gameCtrlr){
	if (!gameCtrlr){
		return;
	}
	SDL_JoystickClose(gameCtrlr);
}

