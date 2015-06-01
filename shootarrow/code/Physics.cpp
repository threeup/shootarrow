#include "Physics.h"


Physics::Physics()
{
}


Physics::~Physics()
{
}

Physics::Physics(const Physics& rs) {
	pInstance = rs.pInstance;
}
Physics* Physics::GetInstance()
{
	static Physics theInstance;
	pInstance = &theInstance;
	return pInstance;
}


Physics* Physics::pInstance = nullptr;