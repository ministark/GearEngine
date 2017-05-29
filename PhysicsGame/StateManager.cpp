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

void StateManager::Update()
{
	states.back()->Update();
}


void StateManager::Render()
{
	states.back()->Render();
}

StateManager::~StateManager()
{
}
