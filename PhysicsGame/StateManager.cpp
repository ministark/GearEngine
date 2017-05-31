#include "StateManager.h"
using namespace Gear;

StateManager* StateManager::inst = NULL;

StateManager::StateManager(GearEngine *eng)
{
	geareng = eng;
}

void StateManager::AddState(State * s)
{
	states.push_back(s);
}

void StateManager::RemoveState()
{
	states.pop_back();
}

void Gear::StateManager::ClearStack()
{
	states.clear();
}

void StateManager::Inputhandle()
{
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		auto ite = states.rbegin();
		while (ite != states.rend()) {
			(*ite)->InputHandle(&msg);
			if (states.empty()) return;
			if ((*ite)->InputCallBack)
				ite++;
			else
				break;
		}
	}
}

void Gear::StateManager::Update()
{
	if (states.empty()) return;
	auto ite = states.rbegin();
	while ( ite != states.rend()) {
		(*ite)->Update(); 
		if ((*ite)->UpdateCallBack)
			ite++;
		else
			break;
	}
}

bool Gear::StateManager::RunScene()
{
	if (states.empty()) return true;
	Inputhandle(); 	

	Update();
	
	Render();

	return false;
}

StateManager * Gear::StateManager::GetInstance( GearEngine* eng)
{
	if (!inst) {
		inst = new StateManager(eng);
	}
	return inst;
}


void StateManager::Render()
{
	if (states.empty()) return;
	geareng->InitRender();
	auto ite = states.rbegin();
	while ( ite != states.rend()) {
		(*ite)->Render(); 
		if ((*ite)->RenderCallBack)
			ite++;
		else
			break;
	}
	geareng->CleanRender();

}

StateManager::~StateManager()
{
}
