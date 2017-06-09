#include "GearDistanceJointX.h"
using namespace Gear;


GearDistanceJointX::GearDistanceJointX()
{
}

GearDistanceJointX::GearDistanceJointX(GearPhysicsBody * b1, GearPhysicsBody *b2, float dist, float stiff, float damp)
{
	body1 = b1;  body2 = b2;
	Distance = dist; // Stores the distance square for optimization
	Stiffness = stiff;
	Dampning = damp;
}

void GearDistanceJointX::ResolveConstraint()
{
	float dr = (body1->_pos._x - body2->_pos._x);
	float force = Stiffness*(dr - Distance) + Dampning*((dr > 0 ? 1 : -1)*(body1->_vel._x - body2->_vel._x));
	if (body1->state != PHYSICS_STATIC) {
		body1->_vel._x += (dr > 0 ? -1 : 1)*force*body1->invmass*PHYSICS_DT;
	}
	if (body2->state != PHYSICS_STATIC) {
		body2->_vel._x += (dr > 0 ? 1 : -1)*force*body2->invmass*PHYSICS_DT;
	}
	
}


GearDistanceJointX::~GearDistanceJointX()
{
}
