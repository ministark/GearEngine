#include "Constants.h"
#pragma once
class Walls
{
	Gear::GearPhysicsBody *left_wall, *right_wall, *bottom_wall, *top_wall;
public:
	Walls(Gear::GearEngine*);
	~Walls();
};

