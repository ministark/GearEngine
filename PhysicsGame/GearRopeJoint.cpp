#include "GearRopeJoint.h"
using namespace Gear;


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
	GearVector dr = body1->_pos - body2->_pos;	float len = dr.norm();
	GearVector dv = (body1->_vel - body2->_vel);
	float force = Stiffness*(len - Distance) +  Dampning*(dv*dr)/len;
	if (len - Distance > 0) {
			body1->_vel -= dr*force*body1->invmass*PHYSICS_DT;
			body2->_vel += dr*force*body2->invmass*PHYSICS_DT;
		}
	}
}


GearRopeJoint::~GearRopeJoint()
{
}
