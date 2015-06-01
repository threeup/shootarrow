#pragma once

#include "Entity.h"

class Camera
{
public:
	Camera();
	~Camera();

	void DrawEntity(Entity* e);

	int mCamPosX;
	int mCamPosY;
};

