#pragma once
#include <memory>
#include "Entity.h"
class Actor :
	public Entity
{
public:
	Actor();
	~Actor();
};

typedef std::shared_ptr<Actor> Actor_ptr;
