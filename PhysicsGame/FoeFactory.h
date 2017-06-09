#include <vector>
#include "Constants.h"
#include "Projectile.h"
#include "Protagonist.h"
#include "Foe.h"
#pragma once
class FoeFactory
{
	std::list<Foe*> enemies;
	Gear::GearEngine *geareng;
	Protagonist *main;
public:
	FoeFactory(Gear::GearEngine*, Protagonist*);
	void addEnemy();
	void UpdateAI(std::list<Projectile*> &);
	void Render();
	void Clean();
	~FoeFactory();
};

