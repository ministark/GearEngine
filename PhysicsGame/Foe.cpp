#include "Foe.h"

void foeOnCollision(void* A, void* B) {
	GearPhysicsBody *body1 = (GearPhysicsBody*)A;
	GearPhysicsBody *body2 = (GearPhysicsBody*)B;
	
	//Hope the Dependency injection works
	Foe *foe = (Foe*)body1->parent;

	//Condition of collision
	if (body2->ObjectType == PLAYER) {
	
	}
	else if (body2->ObjectType == FOE) {
		
	}
	else if (body2->ObjectType == BULLET) {
		foe->health -= BULLET_DAMAGE;
		if (foe->health <= 0) {
			foe->dead = 1;
		}

	}
	else if (body2->ObjectType == WALL) {
	
	}
	else if (body2->ObjectType == GROUND) {
		body1->vx > 0 ? body1->vx = max(0, body1->vx - PLAYER_FRICTION) : body1->vx = min(0, body1->vx + PLAYER_FRICTION);
	}

}

Foe::Foe(GearEngine *geareng)
{
	image = geareng->CreateSprite(50, 82, "Image/Enemy/Enemy.png");
	float x = rand();
	body = geareng->CreatePhysicsBody(	(rand() % SCREEN_WIDTH)-(SCREEN_WIDTH/2),
										(rand() % SCREEN_HEIGHT) - (SCREEN_HEIGHT / 2),
										/*(rand()%(2*FOE_SPEEDX)) - (FOE_SPEEDX)*/0,
										/*(rand()%(2*FOE_SPEEDY)) - (FOE_SPEEDY)*/0,
										50, 82, FOE_INVMASS, 0, PHYSICS_AWAKE);
	body->SetObjectType(FOE);
	body->SetOnCollisionListener(foeOnCollision);
	body->SetImage(image);
	body->SetParent((void*)this);
	health = FOE_HEALTH;
	dead = 0;
}

void Foe::Render()
{
	body->Render();
}


Foe::~Foe()
{
}
