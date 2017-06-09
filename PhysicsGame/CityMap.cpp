#include "CityMap.h"
using namespace Gear;


CityMap::CityMap(GearEngine *eng)
{
	geareng = eng;
	
}

void CityMap::Init()
{
	background = geareng->CreateSprite(SCREEN_WIDTH, SCREEN_HEIGHT, "Image/Background/LensFlare2.png");
	sun = geareng->CreateSprite(518, 659, "Image/Background/Sun.png");

	black = geareng->CreateSprite(100, 100, "Image/Background/Black.png");

	leftwall = geareng->CreatePhysicsBody(GearVector(910, -390), GearVector(0, 0), 100, 300, 0, 0, PHYSICS_STATIC);
	leftwall->SetImage(black);
	leftwall->SetObjectType(GROUND);
	rightwall = geareng->CreatePhysicsBody(GearVector(210, -390), GearVector(0, 0), 100, 300, 0, 0, PHYSICS_STATIC);
	rightwall->SetImage(black);
	rightwall->SetObjectType(GROUND);
	bottomwall = geareng->CreatePhysicsBody(GearVector(0, -510), GearVector(0, 0), 1920, 60, 0, 0, PHYSICS_STATIC);
	bottomwall->SetImage(black);
	bottomwall->SetObjectType(GROUND);
	midwall = geareng->CreatePhysicsBody(GearVector(210,0), GearVector(0, 0), 1500, 60, 0, 0, PHYSICS_STATIC);
	midwall->SetImage(black);
	midwall->SetObjectType(GROUND);
	lhinge = geareng->CreatePhysicsBody(GearVector(880, -250), GearVector(0, 0), 40, 20, 0, 0, PHYSICS_STATIC);
	lhinge->SetImage(black);
	lhinge->SetObjectType(GROUND);
	rhinge = geareng->CreatePhysicsBody(GearVector(240, -250), GearVector(0, 0), 40, 20, 0, 0, PHYSICS_STATIC);
	rhinge->SetImage(black);
	rhinge->SetObjectType(GROUND);
	edges = new Walls(geareng);
	righthinge = geareng->CreatePhysicsBody(GearVector(-750, 500), GearVector(0, 0), 10, 10, 0, 0, PHYSICS_STATIC);
	righthinge->SetImage(black);
	righthinge->SetObjectType(GROUND);
	rightplatform = geareng->CreatePhysicsBody(GearVector(-750, 0), GearVector(0, 0), 400, 60, 0.05, 0, PHYSICS_AWAKE);
	rightplatform->SetImage(black);
	rightplatform->SetObjectType(GROUND);
	geareng->CreateGearDistanceJointY(righthinge, rightplatform, 500, 10, 0);


	for (size_t i = 1; i <= 20; i++)
	{
		bridge.push_back(geareng->CreatePhysicsBody(GearVector(870 - (i * 30), -230), GearVector(0, 0), 20, 10, 10, 0, PHYSICS_AWAKE));
		bridge.back()->SetImage(black);
		bridge.back()->SetObjectType(GROUND);
		if (i!= 1) { geareng->CreateGearRopeJoint(bridge[i-2], bridge[i-1], 25, 20, 1); }
	}
	geareng->CreateGearRopeJoint(bridge[0],lhinge, 25, 20, 1);
	geareng->CreateGearRopeJoint(bridge[19], rhinge, 25, 20, 1);
}

void CityMap::Render()
{
	background->Render(GearVector(0, 0));
	//sun->Render(350 + (main->body->x)*0.1, 100);
	leftwall->RenderX(0,0,0,1,3);
	rightwall->RenderX(0,0,0,1,3);
	bottomwall->RenderX(0, 0, 0, 19.2f, 0.6f);
	midwall->RenderX(0, 0, 0, 15, 0.6f);
	righthinge->RenderX(0, 0, 0, 0.1f, 0.1f);
	rightplatform->RenderX(0, 0, 0, 4, 0.6f);
	for (int i = 0; i < 20; i++) {
		bridge[i]->RenderX(0,0,0,0.2f,0.1f);
	}
	lhinge->RenderX(0,0,0,0.4f,0.2f);
	rhinge->RenderX(0,0,0,0.4f, 0.2f);
}

void CityMap::Reset()
{
}

CityMap::~CityMap()
{
	background->Remove();
	sun->Remove();
	delete edges;
}
