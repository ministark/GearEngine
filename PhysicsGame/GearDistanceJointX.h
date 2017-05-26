#include "GearJoint.h"
#pragma once
class GearDistanceJointX : public GearJoint
{
public:
	//Parameter for the Constrains
	float Distance, Stiffness, Dampning;
	GearDistanceJointX();
	GearDistanceJointX(GearPhysicsBody *,GearPhysicsBody*, float distance, float stiffness, float dampning);
	void ResolveConstraint();
	~GearDistanceJointX();
};

