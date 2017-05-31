#include <vector>
#include "State.h"


#pragma once
namespace Gear {
	class StateManager
	{
	public:
		StateManager(GearEngine *);
		
		// Functions to Change the Active states next frame
		void AddState(State*);
		void RemoveState();
		void ClearStack();
		
		// Run All the Active States
		void Inputhandle();
		void Update();
		void Render();
		
		// Game Loop
		bool RunScene();

		//Singleton Class
		static StateManager* GetInstance(GearEngine*);
		~StateManager();
	private:
		MSG msg;
		GearEngine* geareng;
		std::vector<State*> states;			//	States becomes Active next frame
		std::vector<State*> pstates;		//	States Active this Frame
		static StateManager *inst;
	};
}