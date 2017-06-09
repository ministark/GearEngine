#include "Constants.h"
#pragma once
class Projectile
{
public:
	Gear::GearSprite *img;
	Gear::GearPhysicsBody *body;
	bool dead;
	int type;
	Projectile(Gear::GearEngine*, Gear::GearVector &, Gear::GearVector &);
	void Render();
	bool outOfScreen();
	~Projectile();
private:
	float rot = 0;
};

