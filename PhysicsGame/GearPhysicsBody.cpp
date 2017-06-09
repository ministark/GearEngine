#include "GearPhysicsBody.h"
using namespace Gear;


void GearPhysicsBody::SetImage(GearSprite *img) {image = img;}

void GearPhysicsBody::SetParent(void *prnt)
{
	parent = prnt;
}

GearPhysicsBody::GearPhysicsBody()
{
}


 GearPhysicsBody::GearPhysicsBody(Gear::GearVector &pos, Gear::GearVector &vel, float rw, float rh, float rinvm, float re, int s)
{
	_pos = pos; _vel = vel; width = rw; height = rh; invmass = rinvm; e = re; state = s;
	image = NULL; ObjectType = 0;  OnCollision = NULL;
	markForDeletion = 0;
}



 void GearPhysicsBody::SetOnCollisionListener(EventListner func)
 {
	 OnCollision = func;
 }

 void GearPhysicsBody::SetObjectType(int obj)
 {
	 ObjectType = obj;
 }

void GearPhysicsBody::Render() { 
	if (image != NULL) image->Render(_pos);
}

// Internally calls the sprites Render function
void GearPhysicsBody::RenderX(float rx, float ry, float rz, float scalex, float scaley){
	if (image != NULL) image->RenderX(_pos, rx, ry, rz, scalex, scaley);
}


void GearPhysicsBody::Remove()
{
	markForDeletion = 1;
}



Gear::GearVector GearPhysicsBody::Collide(GearPhysicsBody * b)
{
	float penx = -1*(fabs((_pos-b->_pos)._x)-(width/2)-(b->width/2)), peny = -1*(fabs((_pos-b->_pos)._y)-(height/2)-(b->height)/2);
	if (penx > 0 && peny > 0) {
		return (penx > peny) ? GearVector(0, (b->_pos._y-_pos._y>0 ? 1:-1)*peny): GearVector((b->_pos._x - _pos._x>0 ? 1 : -1)*penx, 0);
	}
	return Gear::GearVector(0,0);
}

GearPhysicsBody::~GearPhysicsBody()
{
}
