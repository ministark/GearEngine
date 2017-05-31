#include <vector>
#include "State.h"


#pragma once
namespace Gear {
	class StateManager
	{
	public:
		StateManager(GearEngine *);
		void AddState(State*);
		void RemoveState();
		void ClearStack();
		void Inputhandle();
		void Update();
		void Render();
		bool RunScene();

		//Singleton Class
		static StateManager* GetInstance(GearEngine*);


		~StateManager();
	private:
		MSG msg;
		GearEngine* geareng;
		std::vector<State*> states;
		static StateManager *inst;
	};
}