#include "Protagonist.h"
using namespace Gear;

void protOnCollision(void* A,void* B) {
	GearPhysicsBody *body1 = (GearPhysicsBody*)A; GearPhysicsBody *body2 = (GearPhysicsBody*)B;
	
	// Dependency Injection
	Protagonist *main = (Protagonist*)body1->parent;
	
	if (body2->ObjectType == PLAYER) {
		
	}
	else if (body2->ObjectType == FOE) {
		body1->_vel._x > 0 ? body1->_vel._x = max(0, body1->_vel._x - PLAYER_FRICTION) : body1->_vel._x = min(0, body1->_vel._x + PLAYER_FRICTION);

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
		body1->_vel._x > 0 ? body1->_vel._x = max(0, body1->_vel._x - PLAYER_FRICTION) : body1->_vel._x = min(0, body1->_vel._x + PLAYER_FRICTION);
	}
	main->isGrounded = 1;
	main->jumptime = 0;
}

void Protagonist::addvx(float vx)
{
	body->_vel._x += vx;

}

void Protagonist::addvy(float vy)
{
	body->_vel._y += vy;
}

Protagonist::Protagonist(GearEngine *geareng)
{
	human	=	geareng->CreateSprite(50, 82, "Image/Character/Ninja.png");
	skel	=	geareng->CreateSprite(50, 73, "Image/Character/Skeleton.png");
	body	=	geareng->CreatePhysicsBody(GearVector(-100, -100),GearVector( 0, 0), 50, 82, PLAYER_INVMASS, 0, PHYSICS_AWAKE);
	body->SetImage(human);
	body->SetParent((void*)this);
	body->SetObjectType(PLAYER);
	body->SetOnCollisionListener(protOnCollision);
	ishuman = 1;
	health = PLAYER_HEALTH;
	jumptime = 0;
}

void Protagonist::Update()
{
	if (jumptime < PLAYER_JUMP_TIME)
		jumptime += 1;
	else
		isGrounded = 0;
}

void Protagonist::Render()
{
	
	(ishuman) ?	body->SetImage(human) : body->SetImage(skel);
	body->Render();
}


Protagonist::~Protagonist()
{
}

