#pragma once
#include <memory>
#include "Entity.h"
class Actor :
	public Entity
{
public:
	Actor(int w, int h);
	~Actor();
};

typedef std::shared_ptr<Actor> Actor_ptr;
