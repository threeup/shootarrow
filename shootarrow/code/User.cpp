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
		userActor->mPosX = clamp(userActor->mPosX + currentInput.x, -100, 100);
	}
	if (currentInput.y != 0)
	{
		userActor->mPosY = clamp(userActor->mPosY + currentInput.y, -100, 100);
	}
}