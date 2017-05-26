#include "Constants.h"
#pragma once
class Foe
{
	GearSprite *image;
public:
	GearPhysicsBody  *body;
	int health;
	bool dead;
	Foe(GearEngine*);
	void Render();
	~Foe();
};

