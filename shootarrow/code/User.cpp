#include "User.h"


User::User(bool isAI)
{
	mIsAI = isAI;
}


User::~User()
{
}

inline int clamp(int x, int a, int b)
{
	return x < a ? a : (x > b ? b : x);
}

void User::DecideInput()
{
	static int tick = 0;
	tick++;
	if (tick > 200)
	{
		tick = 0;
	}
	else if (tick > 100)
	{
		currentInput.x = 1;
		currentInput.y = 1;
	}
	else
	{
		currentInput.x = -1;
		currentInput.y = -1;
	}
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
		userActor->mPosX = clamp(userActor->mPosX + currentInput.x * 3, -300, 300);
	}
	if (currentInput.y != 0)
	{
		userActor->mPosY = clamp(userActor->mPosY + currentInput.y * 3, -200, 200);
	}
}