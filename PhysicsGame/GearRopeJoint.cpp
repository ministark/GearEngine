#include "GearRopeJoint.h"



GearRopeJoint::GearRopeJoint()
{
}

GearRopeJoint::GearRopeJoint(GearPhysicsBody *b1, GearPhysicsBody *b2, float dist, float stiff, float damp)
{
	body1 = b1;
	body2 = b2;
	Distance = dist;
	Stiffness = stiff;
	Dampning = damp;
}

void GearRopeJoint::ResolveConstraint()
{
	// Resolve the constrain
	float dx = (body1->x - body2->x), dy = (body1->y - body2->y), dr2 = dx*dx + dy*dy, dr = std::sqrt(dr2);
	float dvx = (body1->vx - body2->vx), dvy = (body1->vy - body2->vy);
	float force = Stiffness*(dr - Distance) + (dr - Distance > 0 ? -1 : 1)*Dampning*(std::sqrt(pow(dvx, 2) + pow(dvy, 2)));
	if (force > 0) {
		body1->vx += force*body1->invmass*PHYSICS_DT*-dx / dr;
		body1->vy += force*body1->invmass*PHYSICS_DT*-dy / dr;
		body2->vx += force*body2->invmass*PHYSICS_DT* dx / dr;
		body2->vy += force*body2->invmass*PHYSICS_DT* dy / dr;
	}
}


GearRopeJoint::~GearRopeJoint()
{
}