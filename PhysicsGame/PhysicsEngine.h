#include "Constants.h"
#include "Character.h"
#include "Background.h"
#include "Aim.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "World.h"
#pragma once
class PhysicsEngine
{
public:
	PhysicsEngine();
	bool Run(HGE*,HTEXTURE&,World*,float speed);
	~PhysicsEngine();
};

