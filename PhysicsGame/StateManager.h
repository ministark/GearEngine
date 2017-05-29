#include <vector>
#include "State.h"

#pragma once
namespace Gear {
	class StateManager
	{
	public:
		StateManager();
		void AddState(State*);
		void RemoveState();
		void Inputhandle(MSG*);
		bool RunScene(MSG*);
		void Render();
		~StateManager();
	private:
		std::vector<State*> states;
	};
}