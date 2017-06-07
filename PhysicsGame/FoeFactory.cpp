#include "FoeFactory.h"



FoeFactory::FoeFactory(GearEngine *eng, Protagonist *m)
{
	geareng = eng;
	main = m;
	addEnemy();
	addEnemy();
	addEnemy();
	addEnemy();

}

void FoeFactory::addEnemy()
{
	enemies.push_back(new Foe(geareng));
}

void FoeFactory::UpdateAI(std::list<Projectile*> &stars)
{
	if (rand() % 10 == 0) {
		if (!enemies.empty() && main != NULL ) {
			for (auto ite = enemies.begin(); ite != enemies.end(); ++ite) {
				if (rand() % 10 == 0)stars.push_back(new Projectile(	geareng, (*ite)->body->x, 
																		(*ite)->body->y, 
																		(main->body->x - (*ite)->body->x) * BULLET_SPEED, 
																		(main->body->y + 200 - (*ite)->body->y) * BULLET_SPEED  
																	) );
			}
		}
	}
}

void FoeFactory::Render()
{
	for (std::list<Foe*>::iterator ite = enemies.begin(); ite != enemies.end(); ite++) {
		(*ite)->Render();
	}
}

void FoeFactory::Clean()
{
	std::list<Foe*>::iterator ite = enemies.begin();
	while (ite != enemies.end()) {
		if ((*ite)->dead) {
			(*ite)->body->Remove();
			delete (*ite);
			ite = enemies.erase(ite);
		}
		else {
			ite++;
		}
	}
}

FoeFactory::~FoeFactory()
{
}
