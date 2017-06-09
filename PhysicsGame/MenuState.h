#include "StateManager.h"
#include "PlayState.h"
#include "Button.h"
#pragma once
using namespace Gear;

class MenuState : public Gear::State
{
public:
	void Init();
	void Cleanup();
	void Pause();
	void Resume();
	void InputHandle(MSG*);
	void Update();
	void Render();

	//Singleton Functions
	static MenuState* GetInstance(GearEngine*);

	~MenuState();
private:
	GearEngine* geareng;
	MenuState(GearEngine* );
	GearSprite *bpimg, *beimg;
	Button *bplay, *bexit;
	
	static MenuState* inst;
};

