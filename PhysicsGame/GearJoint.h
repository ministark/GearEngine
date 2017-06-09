#include "GearPhysicsBody.h"
#include "GearSettings.h"
#pragma once
namespace Gear {
	class GearJoint
	{
	public:
		GearJoint();
		GearPhysicsBody *body1;
		GearPhysicsBody *body2;
		virtual void ResolveConstraint() = 0;
		~GearJoint();
	};
}
