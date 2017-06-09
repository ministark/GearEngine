#include "GearDistanceJointY.h"
using namespace Gear;


GearDistanceJointY::GearDistanceJointY()
{
}

GearDistanceJointY::GearDistanceJointY(GearPhysicsBody * b1, GearPhysicsBody *b2, float dist, float stiff, float damp)
{
	body1 = b1;  body2 = b2;
	Distance = dist; // Stores the distance square for optimization
	Stiffness = stiff;
	Dampning = damp;
}

void GearDistanceJointY::ResolveConstraint()
{
	float dr = (body1->_pos._y - body2->_pos._y);
	float force = Stiffness*(dr-Distance) + Dampning*((dr > 0 ? 1:-1)*(body1->_vel._y - body2->_vel._y));
	body1->_vel._y += (dr > 0 ? -1 : 1)*force*body1->invmass*PHYSICS_DT;
	body2->_vel._y += (dr > 0 ? 1 : -1)*force*body2->invmass*PHYSICS_DT;

}


GearDistanceJointY::~GearDistanceJointY()
{
}
