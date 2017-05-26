#include "Constants.h"
#pragma once
class Walls
{
	GearPhysicsBody *left_wall, *right_wall, *bottom_wall, *top_wall;
public:
	Walls(GearEngine*);
	~Walls();
};

