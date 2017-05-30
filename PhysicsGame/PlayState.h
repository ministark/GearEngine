#include "State.h"
#include "StateManager.h"
#include "Constants.h"
#include "Walls.h"
#include "Protagonist.h"
#include "FoeFactory.h"
#include "Projectile.h"
#pragma once

class PlayState: public Gear::State
{
public:
	//Virtual Redefination
	void Init();
	void Cleanup();
	void Pause();
	void Resume();
	State* InputHandle(MSG*);
	void Update();
	void Render();

	//GetInstance for this class being Singleton
	static PlayState* GetInstance(GearEngine *);
	void ResetInstance();
	~PlayState();

	//Scene Variables
	Walls *edges;
	Protagonist *main;
	Foe *foe;
	FoeFactory *efac;
	std::list<Projectile*> stars;

private:
	PlayState(GearEngine*);
	static PlayState *inst ;
};

