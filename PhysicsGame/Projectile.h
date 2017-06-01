#include "Constants.h"
#pragma once
class Projectile
{
public:
	GearSprite *img;
	GearPhysicsBody *body;
	bool dead;
	int type;
	Projectile(GearEngine*, float, float, float, float);
	void Render();
	bool outOfScreen();
	~Projectile();
private:
	float rot = 0;
};

