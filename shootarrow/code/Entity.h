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

	int mPosX;
	int mPosY;
	int mPosZ;

	int mExtentsX;
	int mExtentsY;
	int mExtentsZ;
	
	bool mIsVisible;
	bool mIsCollidable;

	LTexture mTexture;
};

