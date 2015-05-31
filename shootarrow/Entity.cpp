#include "Entity.h"


Entity::Entity()
{
	mIsVisible = false;
}


Entity::~Entity()
{
}

void Entity::LoadTexture(std::string s)
{
	if (mTexture.loadFromFile(s))
	{
		mIsVisible = true;
	}
}

void Entity::Draw()
{

}
