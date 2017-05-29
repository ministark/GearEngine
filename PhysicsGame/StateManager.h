#include <vector>

#include "State.h"
#pragma once

namespace GearEngine {
	class StateManager
	{
	public:
		StateManager();
		void AddState(State*);
		void RemoveState();
		void Update();
		void Render();
		~StateManager();
	private:
		std::vector<State*> states;
	};
}
