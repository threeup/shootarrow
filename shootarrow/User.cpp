#include "User.h"


User::User()
{
}


User::~User()
{
}

inline int clamp(int x, int a, int b)
{
	return x < a ? a : (x > b ? b : x);
}

void User::HandleInput()
{
	if (userActor == NULL)
	{
		printf("Input no actor\n");
		return;
	}
	if (currentInput.x != 0)
	{
		userActor->mPosX += currentInput.x;
		userActor->mPosX = clamp(userActor->mPosX, -100, 100);
		printf("Input X %d\n",userActor->mPosX);
	}
	if (currentInput.y != 0)
	{
		userActor->mPosY += currentInput.y;
	}
}