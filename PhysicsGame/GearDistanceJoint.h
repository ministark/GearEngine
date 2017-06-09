#include "GearJoint.h"
#pragma once
/*
	A Distance Joint is technically a Spring 

	Note	:	If objects Spawns way of distance, abnormal behaviour is expected
				Also Dampness should be low in such cases			
	Fix		:	Keep them close or Reduce the Stiffness and Dampning 

*/
namespace Gear {
	class GearDistanceJoint : public GearJoint
	{
	public:
		float Distance, Stiffness, Dampning;
		GearDistanceJoint();
		GearDistanceJoint(GearPhysicsBody *, GearPhysicsBody*, float distance, float stiffness, float dampning);
		void ResolveConstraint();
		~GearDistanceJoint();
	};
}
