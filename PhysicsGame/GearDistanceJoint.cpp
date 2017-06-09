#include "GearDistanceJoint.h"
using namespace Gear;


GearDistanceJoint::GearDistanceJoint()
{
}

GearDistanceJoint::GearDistanceJoint(GearPhysicsBody *b1, GearPhysicsBody *b2, float dist, float stiff, float damp)
{
	body1 = b1;  body2 = b2;
	Distance = dist; // Stores the distance square for optimization
	Stiffness = stiff;
	Dampning = damp;
}


void GearDistanceJoint::ResolveConstraint()
{
	GearVector dr = body1->_pos - body2->_pos;	float len = dr.norm();
	GearVector dv = (body1->_vel - body2->_vel);
	float force = Stiffness*(len - Distance) + Dampning*(dv*dr) / len;
	body1->_vel -= dr*force*body1->invmass*PHYSICS_DT;
	body2->_vel += dr*force*body2->invmass*PHYSICS_DT;
}
GearDistanceJoint::~GearDistanceJoint()
{
}
