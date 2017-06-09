#include "Constants.h"
#pragma once
class Foe
{
	Gear::GearSprite *image;
public:
	Gear::GearPhysicsBody  *body;
	int health;
	bool dead;
	Foe(Gear::GearEngine*);
	void Render();
	~Foe();
};

