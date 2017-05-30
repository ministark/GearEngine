#include "PlayState.h"

using namespace Gear;

PlayState* PlayState::inst = NULL;

PlayState::PlayState(GearEngine* eng)
{
	geareng = eng;
	InputCallBack = 0;
	RenderCallBack = 0;
	UpdateCallBack = 0;
	Init();
}

void PlayState::Init()
{
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

void PlayState::Cleanup()
{
	delete edges;
	delete main;
	delete foe;
	delete efac;
}

void PlayState::Pause()
{
	pause = 1;
}

void PlayState::Resume()
{
	pause = 0;
}

State* PlayState::InputHandle(MSG* msg)
{

	return nullptr;
}

void PlayState::Update()
{
	//Time step could be introduced here
}

void PlayState::Render()
{
	geareng->InitRender();
	main->Render();
	foe->Render();
	efac->Render();
	for (std::list<Projectile*>::iterator ite = stars.begin(); ite != stars.end(); ite++) {
		(*ite)->Render();
	}
	//Remove stars
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

	//Clear all the deleted physicsbody
	geareng->CleanRender();
	//StateManager *inst = StateManager::GetInstance();
}

PlayState* PlayState::GetInstance(GearEngine* eng)
{
	if (!inst) {
		inst = new PlayState(eng);
	}
	return inst;
}

void PlayState::ResetInstance()
{
	Init();
}


PlayState::~PlayState()
{
}

