#pragma once

#include <string>
#include "LTexture.h"

class Entity
{
public:
	Entity();
	~Entity();

	void Draw();
	void LoadTexture(std::string s);

	int mPosX = 0;
	int mPosY = 0;
	int mPosZ = 0;

	int mExtentsX = 0;
	int mExtentsY = 0;
	int mExtentsZ = 0;
	
	bool mIsVisible = false;
	bool mIsCollidable = false;

	LTexture mTexture;
};

