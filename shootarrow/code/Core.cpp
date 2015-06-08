#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <memory>
#include <stdio.h>
#include <string>
#include <cmath>
#include "cleanup.h"
#include "Core.h"
#include "User.h"
#include "LTexture.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
const int TRIGGER_DEAD_ZONE = 0;

Core::Core()
{
	mCamera = new Camera();
}
Core::~Core()
{

}

Core::Core(const Core& rs) {
	pInstance = rs.pInstance;
}
Core* Core::GetInstance()
{
	static Core theInstance;
	pInstance = &theInstance;
	return pInstance;
}

void Core::CoreStart()
{
	mDirector = new Director();
	//mDirector->WorldStart();
	//mDirector->ActorStart();
}

void Core::ClearData()
{
	cleanup(gGameController);
	gGameController = NULL;

	cleanup(gRenderer);
	gRenderer = NULL;

	cleanup(gWindow);
	gWindow = NULL;
}





void Core::CoreLoopTick(bool& quit)
{
	PollEvents(quit);


	bool sdlWindow = false;

	if (sdlWindow)
	{
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);


		for (std::vector<Entity_ptr>::const_iterator iterator = mDirector->worldList.begin(),
			end = mDirector->worldList.end();
			iterator != end;
		++iterator)
		{
			Entity_ptr entity = *iterator;
			mCamera->DrawEntity(entity);
		}

		for (std::vector<Entity_ptr>::const_iterator iterator = mDirector->actorList.begin(),
			end = mDirector->actorList.end();
			iterator != end;
		++iterator)
		{
			Entity_ptr entity = *iterator;
			mCamera->DrawEntity(entity);
		}

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
}

void Core::PollEvents(bool &quit)
{
	//Event handler
	SDL_Event e;

	for (std::vector<User_ptr>::const_iterator iterator = userList.begin(), 
		end = userList.end();
		iterator != end;
		++iterator)
	{
		User_ptr user = *iterator;
		user->lastInput = user->currentInput;
	}

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
			return;
		}

		if (e.type == SDL_JOYAXISMOTION )
		{
			if ((int)e.jaxis.which >= (int)userList.size())
			{
				//ignore
			}
			else
			{
				InputData inputData = userList[e.jaxis.which]->currentInput;
				if (e.jaxis.axis == 0)
				{
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						inputData.x = -1;
					}
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						inputData.x = 1;
					}
					else
					{
						inputData.x = 0;
					}
				}
				else if (e.jaxis.axis == 1)
				{
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						inputData.y = -1;
					}
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						inputData.y = 1;
					}
					else
					{
						inputData.y = 0;
					}
				}
				else if (e.jaxis.axis == 4)
				{
					if (e.jaxis.value > TRIGGER_DEAD_ZONE)
					{
						inputData.trig = 1;
					}
					else
					{
						inputData.trig = 0;
					}
				}
				userList[e.jaxis.which]->currentInput = inputData;
			}
		}

		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			if ((int)e.jbutton.which >= (int)userList.size())
			{
				//ignore
			}
			else
			{
				InputData inputData = userList[e.jbutton.which]->currentInput;
				switch (e.jbutton.button)
				{
				case 0: inputData.hatU = true; break;
				case 1: inputData.hatD = true; break;
				case 2: inputData.hatL = true; break;
				case 3: inputData.hatR = true; break;
				case 10: inputData.btnX = true; break;
				case 11: inputData.btnO = true; break;
				case 8: inputData.btnTrig = true; break;
				case 6: inputData.btnJoy = true; break;
				}
				userList[e.jaxis.which]->currentInput = inputData;
			}
		}
	}//end while

	for (std::vector<User_ptr>::const_iterator iterator = userList.begin(), end = userList.end();
		iterator != end;
		++iterator)
	{
		User_ptr user = *iterator;
		if (user->mIsAI)
		{
			user->DecideInput();
		}
		user->HandleInput();
	}
}

Core* Core::pInstance = nullptr;