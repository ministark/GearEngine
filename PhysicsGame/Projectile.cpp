#include "Projectile.h"
using namespace Gear;
void projOnCollision(void* A, void* B) {
	GearPhysicsBody *body1 = (GearPhysicsBody*)A; GearPhysicsBody *body2 = (GearPhysicsBody*)B;
	
	// Dependency Injection
	Projectile *star = (Projectile*)body1->parent;
	
	//Check all the condition
	if (body2->ObjectType == PLAYER) {
		star->dead = 1;
	}
	else if (body2->ObjectType == FOE) {
		star->dead = 1;
	}
	else if (body2->ObjectType == BULLET) {

	}
	else if (body2->ObjectType == WALL) {
		star->dead = 1;
	}
	else if (body2->ObjectType == GROUND) {
		star->dead = 1;
	}
	else {
		star->dead = 1;
	}
}

Projectile::Projectile(GearEngine* geareng, GearVector &pos, GearVector &vel)
{
	img = geareng->CreateSprite(25, 25, "Image/Bullet/Star.png");
	body = geareng->CreatePhysicsBody(pos, vel, 25, 25, BULLET_INVMASS, BULLET_E, PHYSICS_AWAKE);
	body->SetObjectType(BULLET);
	body->SetImage(img);
	body->SetParent((void*)this);
	body->SetOnCollisionListener(projOnCollision);
	dead = 0; // Alive when Born no spwan kill
}

void Projectile::Render()
{
	rot -= (body->_vel._x > 0 ? 1 : -1)*(fabs(body->_vel._x) + fabs(body->_vel._y))*BULLET_ANIMATION;
	body->RenderX(0,0,rot,1,1);
}

bool Projectile::outOfScreen()
{
	return (fabs(body->_pos._x) > SCREEN_WIDTH / 2 && fabs(body->_pos._y) > SCREEN_HEIGHT / 2);
}


Projectile::~Projectile()
{
}
