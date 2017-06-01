#include <math.h>
#include "GearSettings.h"
#include "GearSprites.h"
#pragma once
typedef  void(*EventListner)(void*, void*);
class GearPhysicsBody
{
public:
	float x, y, vx, vy, width, height, invmass, e;
	bool markForDeletion;
	void *parent; //To store the parent of this Body
	void SetParent(void*);
	int ObjectType;
	int state;
	EventListner OnCollision;
	GearSprite *image;
	GearPhysicsBody();
	GearPhysicsBody(float,float,float,float,float,float,float,float,int);
	void SetOnCollisionListener(EventListner);
	void SetObjectType(int);
	void SetImage(GearSprite*);
	void Render();
	void RenderX(float rx, float ry, float rz, float scale);

	void Remove();
	float Collide(GearPhysicsBody*);
	~GearPhysicsBody();
};

