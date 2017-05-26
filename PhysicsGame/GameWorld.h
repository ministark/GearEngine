#include "Constants.h"
#include "Walls.h"
#include "Protagonist.h"
#include "FoeFactory.h"
#include "Projectile.h"
#pragma once

class GameWorld
{
	Walls *edges;
	GearEngine *geareng;
public:
	Protagonist *main;
	Foe *foe;
	FoeFactory *efac;
	std::list<Projectile*> stars;
	void addStar(float, float, float, float);
	bool kw, ka, ks, kd, kshift, mleft;
	bool pkw, pmleft, pkshift;
	void setPrev();
	short mx, my;
	GameWorld(GearEngine*);
	void Render();
	void Clean();
	~GameWorld();
};

