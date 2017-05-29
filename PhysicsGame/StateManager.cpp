#include "StateManager.h"
using namespace GearEngine;


StateManager::StateManager()
{
}

void GearEngine::StateManager::AddState(State * s)
{
	states.push_back(s);
}

void GearEngine::StateManager::RemoveState()
{
	states.pop_back();
}

void GearEngine::StateManager::Update()
{
	states.back()->Update();
}


void GearEngine::StateManager::Render()
{
	states.back()->Render();
}

StateManager::~StateManager()
{
}
