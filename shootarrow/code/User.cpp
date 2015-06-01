#include "User.h"
#include <ctime>

User::User(bool isAI)
{
	mIsAI = isAI;
	tick = 0;
	decision = 0;
	start = std::clock();
}


User::~User()
{
}

inline int clamp(int x, int a, int b)
{
	return x < a ? a : (x > b ? b : x);
}

inline int wrap(int x, int a, int b)
{
	return x == b ? 0 : x + a;
}


void User::DecideInput()
{
	tick++;
	if (tick > 100)
	{
		decision = wrap(decision, 1, 3);
		if (decision == 0)
		{
#ifdef __unix__
			double duration = (std::clock() - start) * 0.85;
			double fps = 400 / duration * 1000000;
			printf("duration%f  %f\n", duration, fps);
#endif
#ifdef _WIN32
			double duration = std::clock() - start;
			double fps = 400 / duration * 1000;
			printf("duration%f  %f\n", duration, fps);
#endif            
			start = std::clock();
		}
		tick = 0;
	}
	switch (decision)
	{
	case 0:
		currentInput.x = 1;
		currentInput.y = 0;
		break;
	case 1:
		currentInput.x = 0;
		currentInput.y = 1;
		break;
	case 2:
		currentInput.x = -1;
		currentInput.y = 0;
		break;
	case 3:
		currentInput.x = 0;
		currentInput.y = -1;
		break;
	}
}

void User::HandleInput()
{
	if (userActor == NULL)
	{
		printf("Input no actor\n");
		return;
	}
#ifdef __unix__
	int speed = 3;
#endif
#ifdef _WIN32
	int speed = 2;
#endif
	if (currentInput.x != 0)
	{
		userActor->mPosX = clamp(userActor->mPosX + currentInput.x * speed, -300, 300);
	}
	if (currentInput.y != 0)
	{
		userActor->mPosY = clamp(userActor->mPosY + currentInput.y * speed, -200, 200);
	}
}