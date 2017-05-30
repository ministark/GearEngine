#include "StateManager.h"
using namespace Gear;

StateManager* StateManager::inst = NULL;

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

void Gear::StateManager::ClearStack()
{
	states.clear();
}

void StateManager::Inputhandle(MSG* msg)
{
	auto ite = states.rbegin();
	while ((*ite)->InputCallBack && ite != states.rend()) {
		(*ite)->InputHandle(msg); ite++;
	}
}

void Gear::StateManager::Update()
{
	auto ite = states.rbegin();
	while ((*ite)->UpdateCallBack && ite != states.rend()) {
		(*ite)->Update(); ite++;
	}
}

bool Gear::StateManager::RunScene(MSG *msg)
{
	if (states.empty()) return true;

	Inputhandle(msg);
	Update();
	Render();

	return false;
}

StateManager * Gear::StateManager::GetInstance()
{
	if (!inst) {
		inst = new StateManager();
	}
	return inst;
}


void StateManager::Render()
{
	auto ite = states.rbegin();
	while ( ite != states.rend()) {
		(*ite)->Render(); 
		if ((*ite)->RenderCallBack)
			ite++;
		else
			break;
	}
}

StateManager::~StateManager()
{
}
