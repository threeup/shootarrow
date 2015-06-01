#pragma once
#include "Actor.h"
#include "InputData.h"

class User
{
public:
	User(bool isAI);
	~User();

	void DecideInput();
	void HandleInput();

	bool mIsAI;
	Actor* userActor;
	InputData currentInput;
	InputData lastInput;

private:
	int tick;
	double start;
};

