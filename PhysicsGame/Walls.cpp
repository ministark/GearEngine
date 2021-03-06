#include "Walls.h"

using namespace Gear;

Walls::Walls(GearEngine *geareng)
{
	left_wall	=	geareng->CreatePhysicsBody(GearVector(SCREEN_WIDTH/2, 0), GearVector(0, 0), 20, SCREEN_HEIGHT, 0, 1, PHYSICS_STATIC);
	left_wall->SetObjectType(WALL);
	right_wall	=	geareng->CreatePhysicsBody(GearVector (-SCREEN_WIDTH/2, 0), GearVector( 0, 0), 20, SCREEN_HEIGHT, 0, 1, PHYSICS_STATIC);
	right_wall->SetObjectType(WALL);
	bottom_wall =	geareng->CreatePhysicsBody(GearVector(0, -SCREEN_HEIGHT/2), GearVector(0, 0), SCREEN_WIDTH, 20, 0, 1, PHYSICS_STATIC);
	bottom_wall->SetObjectType(GROUND);
	top_wall	=	geareng->CreatePhysicsBody(GearVector(0, SCREEN_HEIGHT / 2), GearVector(0, 0), SCREEN_WIDTH, 20, 0, 1, PHYSICS_STATIC);
	top_wall->SetObjectType(WALL);
}



Walls::~Walls()
{
}
