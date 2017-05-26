
#include "Constants.h"
#pragma once
class Protagonist
{
	GearSprite *human,*skel;
public:
	GearPhysicsBody  *body;
	bool ishuman,isGrounded;
	bool dead;
	int health;
	void addvx(float);
	void addvy(float);
	Protagonist(GearEngine*);
	void Render();
	~Protagonist();
};

