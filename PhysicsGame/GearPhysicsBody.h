#include <math.h>
#include "GearSettings.h"
#include "GearSprites.h"
#include "GearVector.h" 
#pragma once
namespace Gear {
	typedef  void(*EventListner)(void*, void*);
	class GearPhysicsBody
	{
	public:
		Gear::GearVector _pos, _vel;
		float  width, height, invmass, e;
		bool markForDeletion;
		void *parent; //To store the parent of this Body
		void SetParent(void*);
		int ObjectType;
		int state;
		EventListner OnCollision;
		GearSprite *image;
		GearPhysicsBody();
		GearPhysicsBody(Gear::GearVector &, Gear::GearVector &, float, float, float, float, int);
		void SetOnCollisionListener(EventListner);
		void SetObjectType(int);
		void SetImage(GearSprite*);
		void Render();
		void RenderX(float rx, float ry, float rz, float scalex, float scaley);

		void Remove();
		Gear::GearVector Collide(GearPhysicsBody*);
		~GearPhysicsBody();
	};
}