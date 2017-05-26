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
	float dy = fabs(body2->y - body1->y) - Distance;
	float force = Stiffness*dy + (dy > 0 ? -1 : 1)*Dampning*(fabs(body1->vy - body2->vy));
	body1->vy += (body1->y < body2->y ? 1 : -1)*force*body1->invmass*PHYSICS_DT;
	body2->vy += (body2->y < body1->y ? 1 : -1)*force*body2->invmass*PHYSICS_DT;
	//yet to use dampnes;

}


GearDistanceJointY::~GearDistanceJointY()
{
}
