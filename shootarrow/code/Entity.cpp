#include "Entity.h"
#include "Physics.h"


Entity::Entity(int w, int h)
{
	mPosX = 0;
	mPosY = 0;
	mPosZ = 0;

	Physics* phys = Physics::GetInstance();
	mExtentsX = w*phys->cellWidth;
	mExtentsY = h*phys->cellHeight;
	mExtentsZ = w > h ? w : h;

	mIsVisible = false;
	mIsCollidable = false;
}


Entity::~Entity()
{
}

void Entity::SetPos(int x, int y)
{
	mPosX = x;
	mPosY = y;
}
void Entity::SetPos(int x, int y, int z)
{
	mPosX = x;
	mPosY = y;
	mPosZ = z;
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
