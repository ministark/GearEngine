#include "State.h" 
#include "StateManager.h"
#pragma once

class PauseState: public Gear::State
{
public:
	//Virtual Redefination
	void Init();
	void Cleanup();
	void Pause();
	void Resume();
	void InputHandle(MSG*);
	void Update();
	void Render();


	~PauseState();
	static PauseState* GetInstance(GearEngine*);
private:
	GearSprite *pauseimg, *clouds;
	GearEngine *geareng;
	PauseState(GearEngine*);
	static PauseState* inst;
};

