#include "GameWorld.h"


void GameWorld::addStar(float x, float y, float vx, float vy)
{
	stars.push_back(new Projectile(geareng, x, y, vx, vy));
	main->addvx(-vx*PLAYER_RECOIL);
	main->addvy(-vy*PLAYER_RECOIL);

}

void GameWorld::setPrev()
{
	pkw = kw; pkshift = kshift; pmleft = mleft;
}

GameWorld::GameWorld(GearEngine *eng)
{
	geareng = eng;
	//Set the key in the world
	kw = 0; ka = 0; ks = 0; kd = 0; kshift = 0; mleft = 0; mx = 0; my = 0;
	pkw = 0; pmleft = 0; pkshift = 0;
	//Set the enviornment
	edges = new Walls(geareng);
	//Set the Player and AI
	main = new Protagonist(geareng);
	foe = new Foe(geareng);
	//geareng->CreateGearDistanceJointX(main->body,foe->body , 200, 10, 0);
	geareng->CreateGearDistanceJoint(main->body, foe->body, 200, 10, 0);
	//geareng->CreateGearRopeJoint(main->body, foe->body, 400, 100, 10);


	efac = new FoeFactory(geareng);
	efac->addEnemy(geareng);

}

void GameWorld::Render()
{
	main->Render();
	foe->Render();
	efac->Render();
	for (std::list<Projectile*>::iterator ite = stars.begin(); ite != stars.end(); ite++) {
		(*ite)->Render();
	}
}

void GameWorld::Clean() {
	std::list<Projectile*>::iterator ite = stars.begin();
	while (ite != stars.end()) {
		if ((*ite)->dead || (*ite)->outOfScreen()) {
			(*ite)->body->Remove();
			delete (*ite); //Free the heap
			ite = stars.erase(ite);
		}
		else  ite++;
	}
	efac->Clean();
}


GameWorld::~GameWorld()
{
}
