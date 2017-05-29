#include "PlayState.h"

using namespace Gear;

PlayState* PlayState::inst = NULL;

PlayState::PlayState(GearEngine* eng)
{
	geareng = eng;
	InputCallBack = 0;
	RenderCallBack = 0;
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

void PlayState::Render()
{
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

