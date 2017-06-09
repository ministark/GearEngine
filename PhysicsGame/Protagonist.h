
#include "Constants.h"
#pragma once
class Protagonist
{
	Gear::GearSprite *human,*skel;
public:
	Gear::GearPhysicsBody  *body;
	bool ishuman,isGrounded;
	float jumptime;
	bool dead;
	int health;
	void addvx(float);
	void addvy(float);
	Protagonist(Gear::GearEngine*);
	void Update();
	void Render();
	~Protagonist();
};

