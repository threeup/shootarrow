#pragma once

#include <memory>
#include <string>
#include "LTexture.h"

class Entity
{
public:
	Entity(int w, int h);
	~Entity();

	void Draw();
	void SetPos(int x, int y);
	void SetPos(int x, int y, int z);
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

typedef std::shared_ptr<Entity> Entity_ptr;