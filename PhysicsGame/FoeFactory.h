#include <vector>
#include "Constants.h"
#include "Foe.h"
#pragma once
class FoeFactory
{
	std::list<Foe*> enemies;
public:
	FoeFactory(GearEngine*);
	void addEnemy(GearEngine*);
	void Render();
	void Clean();
	~FoeFactory();
};

