#include "GearJoint.h"
#pragma once
namespace Gear {
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
}
