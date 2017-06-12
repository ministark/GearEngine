#include "State.h"
#include "Protagonist.h"
#pragma once
using namespace Gear;
class DebugState : public State
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

	static DebugState* GetInstance(GearEngine *);
	void ResetInstance();
	static DebugState *inst;

	GearEngine *geareng;
	Protagonist *main;

	DebugState(GearEngine *);
	~DebugState();
};

