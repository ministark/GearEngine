#include "PlayState.h"

using namespace Gear;


PlayState::PlayState()
{
}

void PlayState::Init()
{
}

void PlayState::Cleanup()
{
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::Update()
{
}

void PlayState::Render()
{
}

PlayState * PlayState::GetInstance(GearEngine* eng)
{
	geareng = eng;
	if (!instance) {
		instance = new PlayState();
	}
	return instance;
}


PlayState::~PlayState()
{
}
