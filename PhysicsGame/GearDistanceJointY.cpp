#include "GearDistanceJointY.h"



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
	float dr = (body1->y - body2->y);
	float force = Stiffness*(dr-Distance) + Dampning*((dr > 0 ? 1:-1)*(body1->vy - body2->vy));
	if (body1->state != PHYSICS_STATIC) {
		body1->vy += (dr > 0 ? -1 : 1)*force*body1->invmass*PHYSICS_DT;
	}
	if (body2->state != PHYSICS_STATIC) {
		body2->vy += (dr > 0 ? 1 : -1)*force*body2->invmass*PHYSICS_DT;
	}

}


GearDistanceJointY::~GearDistanceJointY()
{
}
