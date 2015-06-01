#pragma once
#include "Actor.h"
#include "InputData.h"

class User
{
public:
	User();
	~User();

	void HandleInput();

	Actor* userActor;
	InputData currentInput;
	InputData lastInput;
};

