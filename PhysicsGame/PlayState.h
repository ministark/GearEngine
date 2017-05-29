#include "State.h"
#include "Constants.h"
#include "Walls.h"
#include "Protagonist.h"
#include "FoeFactory.h"
#include "Projectile.h"
#pragma once

class PlayState: public Gear::State
{
public:
	void Init();
	void Cleanup();
	void Pause();
	void Resume();
	void Update();
	void Render();
	PlayState* GetInstance(GearEngine*);
	~PlayState();
private:
	GearEngine* geareng;
	Walls *edges;
	GearEngine *geareng;
	PlayState();
	static PlayState *instance;
};

