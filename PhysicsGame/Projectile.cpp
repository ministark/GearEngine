#include "Projectile.h"

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
}

Projectile::Projectile(GearEngine* geareng, float rx, float ry, float rvx, float rvy)
{
	img = geareng->CreateSprite(25, 25, "Image/Bullet/Star.png");
	body = geareng->CreatePhysicsBody(rx, ry, rvx, rvy, 25, 25, BULLET_INVMASS, BULLET_E, PHYSICS_AWAKE);
	body->SetObjectType(BULLET);
	body->SetImage(img);
	body->SetParent((void*)this);
	body->SetOnCollisionListener(projOnCollision);
	dead = 0; // Alive when Born no spwan kill
}

void Projectile::Render()
{
	rot -= (body->vx >0 ? 1:-1)*(fabs(body->vx)+fabs(body->vy))*BULLET_ANIMATION;
	body->RenderX(0,0,rot,1);
}

bool Projectile::outOfScreen()
{
	return (fabs(body->x) > SCREEN_WIDTH / 2 && fabs(body->y) > SCREEN_HEIGHT / 2);
}


Projectile::~Projectile()
{
}
