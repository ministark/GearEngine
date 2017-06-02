#include "GameMap.h"
#include "Walls.h"
#pragma once 
class CityMap : public GameMap 
{
public:
	CityMap(GearEngine*);
	void Init();
	void Render();
	void Reset();
private:
	GearSprite  *background, *sun, *black, *black2;
	GearPhysicsBody *leftwall, *rightwall, *lhinge, *rhinge, *bottomwall, *midwall, *rightplatform, *righthinge;
	std::vector<GearPhysicsBody*> bridge;
	Walls *edges;
	~CityMap();
};

