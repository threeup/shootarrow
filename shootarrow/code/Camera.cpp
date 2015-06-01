#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "Camera.h"
#include "Core.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Camera::Camera()
{
	mCamPosX = -SCREEN_WIDTH / 2;
	mCamPosY = -SCREEN_HEIGHT / 2;
}


Camera::~Camera()
{
}




void Camera::DrawEntity(Entity_ptr e)
{
	double angle = 0;
	
	
	SDL_Point* center = (SDL_Point*)0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int x = e->mPosX - mCamPosX;
	int y = e->mPosY - mCamPosY;

	float scaleX = (float)e->mExtentsX / e->mTexture.getWidth();
	float scaleY = (float)e->mExtentsY / e->mTexture.getHeight();
	
	e->mTexture.render(x, y, scaleX, scaleY, angle, center, flip);
}
