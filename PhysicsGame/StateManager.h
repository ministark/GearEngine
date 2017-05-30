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
		void ClearStack();
		void Inputhandle(MSG*);
		void Update();
		void Render();
		bool RunScene(MSG*);

		//Singleton Class
		static StateManager* GetInstance();


		~StateManager();
	private:
		std::vector<State*> states;
		static StateManager *inst;
	};
}