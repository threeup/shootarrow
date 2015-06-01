#pragma once
#include <memory>
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
	Actor_ptr userActor;
	InputData currentInput;
	InputData lastInput;

private:
	int tick;
	double start;
};

typedef std::shared_ptr<User> User_ptr;

