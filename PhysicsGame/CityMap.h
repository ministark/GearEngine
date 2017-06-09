#include "GameMap.h"
#include "Walls.h"
#pragma once 
class CityMap : public GameMap 
{
public:
	CityMap(Gear::GearEngine*);
	void Init();
	void Render();
	void Reset();
private:
	Gear::GearSprite  *background, *sun, *black, *black2;
	Gear::GearPhysicsBody *leftwall, *rightwall, *lhinge, *rhinge, *bottomwall, *midwall, *rightplatform, *righthinge;
	std::vector<Gear::GearPhysicsBody*> bridge;
	Walls *edges;
	~CityMap();
};

