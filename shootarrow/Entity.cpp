#include "Entity.h"


Entity::Entity()
{
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
