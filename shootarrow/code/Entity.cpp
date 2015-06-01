#include "Entity.h"


Entity::Entity()
{
	mPosX = 0;
	mPosY = 0;
	mPosZ = 0;

	mExtentsX = 0;
	mExtentsY = 0;
	mExtentsZ = 0;

	mIsVisible = false;
	mIsCollidable = false;
}


Entity::~Entity()
{
}

void Entity::LoadTexture(std::string s)
{
	if (mTexture.LoadFromFile(s))
	{
		mIsVisible = true;
	}
}

void Entity::Draw()
{

}
