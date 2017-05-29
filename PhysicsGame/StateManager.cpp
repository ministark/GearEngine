#include "StateManager.h"
using namespace Gear;

StateManager::StateManager()
{
}

void StateManager::AddState(State * s)
{
	states.push_back(s);
}

void StateManager::RemoveState()
{
	states.pop_back();
}

void StateManager::Inputhandle(MSG*)
{
}

bool Gear::StateManager::RunScene(MSG *msg)
{
	if (states.empty()) return true;
	auto ite = states.rbegin();
	while ((*ite)->InputCallBack)



	return false;
}


void StateManager::Render()
{
	states.back()->Render();
}

StateManager::~StateManager()
{
}
