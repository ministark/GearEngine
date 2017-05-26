#include "FoeFactory.h"



FoeFactory::FoeFactory(GearEngine *geareng)
{
	
}

void FoeFactory::addEnemy(GearEngine* geareng)
{
	enemies.push_back(new Foe(geareng));
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
