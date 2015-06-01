#pragma once
#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <vector>
#include "Entity.h"
#include "User.h"

class Director
{
public:
	Director();
	~Director();

	void WorldStart();
	void ActorStart();

	std::vector<Entity_ptr> worldList;
	std::vector<Entity_ptr> actorList;
};

