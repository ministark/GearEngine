#include "GearJoint.h"
#pragma once
class GearDistanceJointY : public GearJoint
{
public:
	//Parameter for the Constrains
	float Distance, Stiffness, Dampning;
	GearDistanceJointY();
	GearDistanceJointY(GearPhysicsBody *, GearPhysicsBody*, float distance, float stiffness, float dampning);
	void ResolveConstraint();
	~GearDistanceJointY();
};

