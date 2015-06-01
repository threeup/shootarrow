#pragma once
class Physics
{
	static Physics* pInstance;
	Physics();
	Physics(const Physics& rs);
	~Physics();
public:
	
	static Physics* GetInstance();

	int cellWidth;
	int cellHeight;
};

