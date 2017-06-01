#include "GearPhysicsBody.h"



void GearPhysicsBody::SetImage(GearSprite *img) {image = img;}

void GearPhysicsBody::SetParent(void *prnt)
{
	parent = prnt;
}

GearPhysicsBody::GearPhysicsBody()
{
}


 GearPhysicsBody::GearPhysicsBody(float rx, float ry, float rvx, float rvy, float rw, float rh, float rinvm, float re, int s)
{
	x = rx; y = ry; vx = rvx; vy = rvy; width = rw; height = rh; invmass = rinvm; e = re; state = s;
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
	if (image != NULL) image->Render(x, y);
}

// Internally calls the sprites Render function
void GearPhysicsBody::RenderX(float rx, float ry, float rz, float scale){
	if (image != NULL) image->RenderX(x, y, rx, ry, rz, scale);
}


void GearPhysicsBody::Remove()
{
	markForDeletion = 1;
}



float GearPhysicsBody::Collide(GearPhysicsBody * b)
{
	float penx = -1*(fabs(x-b->x)-(width/2)-(b->width/2)), peny = -1*(fabs(y-b->y)-(height/2)-(b->height)/2);
	if (penx > 0 && peny > 0) {
		if (penx > peny) return PHYSICSY*peny;
		return PHYSICSX*penx;
	}
	return 0;
}

GearPhysicsBody::~GearPhysicsBody()
{
}
