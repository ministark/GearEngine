#include "Constants.h"
#pragma once
class GameMap
{
public:
	GameMap();
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;
	GearEngine *geareng;
	~GameMap();
};

