#include "Protagonist.h"


void protOnCollision(void* A,void* B) {
	GearPhysicsBody *body1 = (GearPhysicsBody*)A; GearPhysicsBody *body2 = (GearPhysicsBody*)B;
	
	// Dependency Injection
	Protagonist *main = (Protagonist*)body1->parent;
	
	if (body2->ObjectType == PLAYER) {
		
	}
	else if (body2->ObjectType == FOE) {
		body1->vx > 0 ? body1->vx = max(0, body1->vx - PLAYER_FRICTION) : body1->vx = min(0, body1->vx + PLAYER_FRICTION);

	}
	else if (body2->ObjectType == BULLET) {
		main->health -= BULLET_DAMAGE;
		if (main->health <= 0) {
			main->dead = 1;
		}
	}
	else if (body2->ObjectType == WALL) {

	}
	else if (body2->ObjectType == GROUND) {
		body1->vx > 0 ? body1->vx = max(0, body1->vx - PLAYER_FRICTION) : body1->vx = min(0, body1->vx + PLAYER_FRICTION);
	}
}

void Protagonist::addvx(float rvx)
{
	body->vx += rvx;

}

void Protagonist::addvy(float rvy)
{
	body->vy += rvy;
}

Protagonist::Protagonist(GearEngine *geareng)
{
	human	=	geareng->CreateSprite(50, 82, "Image/Character/Ninja.png");
	skel	=	geareng->CreateSprite(50, 73, "Image/Character/Skeleton.png");
	body	=	geareng->CreatePhysicsBody(-100, -100, 0, 0, 50, 82, PLAYER_INVMASS, 0, PHYSICS_AWAKE);
	body->SetImage(human);
	body->SetParent((void*)this);
	body->SetObjectType(PLAYER);
	body->SetOnCollisionListener(protOnCollision);
	ishuman = 1;
	health = PLAYER_HEALTH;
}

void Protagonist::Render()
{
	(ishuman) ?	body->SetImage(human) : body->SetImage(skel);
	body->Render();
}


Protagonist::~Protagonist()
{
}

