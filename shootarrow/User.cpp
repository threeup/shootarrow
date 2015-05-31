#include "User.h"


User::User()
{
}


User::~User()
{
}


void User::HandleInput()
{
	if (userActor == NULL)
	{
		return;
	}
	if (currentInput.x != 0)
	{
		userActor->mPosX += currentInput.x;
	}
	if (currentInput.y != 0)
	{
		userActor->mPosY += currentInput.y;
	}
}