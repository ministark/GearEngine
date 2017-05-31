#include "StateManager.h"
#include <algorithm>
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
	//Update Stack as active
	pstates = states;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		auto ite = pstates.rbegin();
		while (ite != pstates.rend()) {
			(*ite)->InputHandle(&msg);
			if ((*ite)->InputCallBack)
				ite++;
			else
				break;
		}
	}
}

void Gear::StateManager::Update()
{
	auto ite = pstates.rbegin();
	while ( ite != pstates.rend()) {
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
	std::vector<State*> tobeRender;
	geareng->InitRender();
	auto ite = pstates.rbegin();
	while ( ite != pstates.rend()) {
		tobeRender.push_back((*ite));
		if ((*ite)->RenderCallBack)
			ite++;
		else
			break;
	}
	auto ite1 = tobeRender.rbegin();
	while (ite1 != tobeRender.rend()) {
		(*ite1)->Render(); ite1++;
	}
	geareng->CleanRender();
	
}

StateManager::~StateManager()
{
}
