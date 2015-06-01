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
#include <fstream>
#include "Director.h"
#include "User.h"
#include "LTexture.h"
#include "Core.h"
#include "Physics.h"
#include "GenericGrid.h"


Director::Director()
{
	
}


Director::~Director()
{
}

void Director::WorldStart()
{
	Physics* phys = Physics::GetInstance();
	GenericGrid<char> map = GenericGrid<char>(17,17);
	
	int rows = map.numRows();
	int cols = map.numColumns(); 
	std::ifstream infile("code/map.txt");
	std::string line;
	for (int j = 0; std::getline(infile, line) && j < rows; ++j)
	{
		for (int i = 0; i < cols; ++i)
		{
			map.set(i, j, line.at(i));
		}
	}

	int screenWidth = 640;
	int screenHeight = 480;
	phys->cellWidth = screenWidth / rows;
	phys->cellHeight = screenHeight / cols;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (map.get(i,j) == 'X')
			{
				Entity_ptr wall(new Entity(1,1));
				wall->LoadTexture("art/wall.png");
				int x = i - rows / 2;
				int y = j - cols / 2;
				wall->SetPos(x * phys->cellWidth, y * phys->cellHeight);
				printf("wall at %d %d\n", x, y);
				worldList.push_back(wall);
			}
		}
	}
}

void Director::ActorStart()
{
	Core* core = Core::GetInstance();
	Actor_ptr human(new Actor(1, 1));
	Actor_ptr aiman(new Actor(1, 1));
	human->LoadTexture("art/monkey.png");
	aiman->LoadTexture("art/pig.png");
	actorList.push_back(human);
	actorList.push_back(aiman);


	User_ptr user0(new User(false));
	User_ptr user1(new User(true));
	user0->userActor = human;
	core->userList.push_back(user0);
	user1->userActor = aiman;
	core->userList.push_back(user1);

}
