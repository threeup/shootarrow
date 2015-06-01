#ifndef CORE_H
#define CORE_H

#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <vector>
#include "LTexture.h"
#include "Camera.h"
#include "Entity.h"
#include "User.h"


class Core
{
	static Core* pInstance;

	Core();

	Core(const Core& rs);


	~Core();

public:

	static Core* GetInstance();
	void ClearData();
	void CoreStart();
	void CoreLoopTick(bool &quit);
	void PollEvents(bool &quit);

	Camera* mCamera;
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Joystick* gGameController;

	std::vector<User_ptr> userList;
	std::vector<Entity_ptr> entityList;

};


#endif