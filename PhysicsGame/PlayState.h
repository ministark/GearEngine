#include "State.h"
#include "PauseState.h"
#include "CityMap.h"
#include "Protagonist.h"
#include "FoeFactory.h"
#include "Projectile.h"
#pragma once

using namespace Gear;
class PlayState: public Gear::State
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

	//GetInstance for this class being Singleton
	static PlayState* GetInstance(GearEngine *);
	void ResetInstance();
	~PlayState();

	//Scene Variables
	std::list<Projectile*> stars;

	//Input Variables
	bool key_w, key_a, key_s, key_d, key_shift, mouse_l, pkey_w, pkey_shift, pmouse_l;
	GearVector mouse;

private:
	GameMap *map;
	Protagonist *main;
	Foe *foe;
	FoeFactory *efac;
	PlayState(GearEngine*);
	static PlayState *inst ;
};

