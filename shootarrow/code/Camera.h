#pragma once

#include "Entity.h"

class Camera
{
public:
	Camera();
	~Camera();

	void DrawEntity(Entity_ptr e);

	int mCamPosX;
	int mCamPosY;
};

