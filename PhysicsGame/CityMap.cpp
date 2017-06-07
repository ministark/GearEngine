#include "CityMap.h"



CityMap::CityMap(GearEngine *eng)
{
	geareng = eng;
	
}

void CityMap::Init()
{
	background = geareng->CreateSprite(SCREEN_WIDTH, SCREEN_HEIGHT, "Image/Background/LensFlare2.png");
	sun = geareng->CreateSprite(518, 659, "Image/Background/Sun.png");

	black = geareng->CreateSprite(100, 100, "Image/Background/Black.png");

	leftwall = geareng->CreatePhysicsBody(910, -390, 0, 0, 100, 300, 0, 0, PHYSICS_STATIC);
	leftwall->SetImage(black);
	rightwall = geareng->CreatePhysicsBody(210, -390, 0, 0, 100, 300, 0, 0, PHYSICS_STATIC);
	rightwall->SetImage(black);
	bottomwall = geareng->CreatePhysicsBody( 0, -510, 0, 0, 1920, 60, 0, 0, PHYSICS_STATIC);
	bottomwall->SetImage(black);
	midwall = geareng->CreatePhysicsBody(210,0, 0, 0, 1500, 60, 0, 0, PHYSICS_STATIC);
	midwall->SetImage(black);
	lhinge = geareng->CreatePhysicsBody(880, -250, 0, 0, 40, 20, 0, 0, PHYSICS_STATIC);
	lhinge->SetImage(black);
	rhinge = geareng->CreatePhysicsBody(240, -250, 0, 0, 40, 20, 0, 0, PHYSICS_STATIC);
	rhinge->SetImage(black);
	edges = new Walls(geareng);
	righthinge = geareng->CreatePhysicsBody(-750, 500, 0, 0, 10, 10, 0, 0, PHYSICS_STATIC);
	righthinge->SetImage(black);
	rightplatform = geareng->CreatePhysicsBody(-750, 0, 0, 0, 400, 60, 0.05, 0, PHYSICS_AWAKE);
	rightplatform->SetImage(black);
	geareng->CreateGearDistanceJointY(righthinge, rightplatform, 500, 10, 0);


	for (size_t i = 1; i <= 20; i++)
	{
		bridge.push_back(geareng->CreatePhysicsBody(870 - (i * 30), -230, 0, 0, 20, 10, 10, 0, PHYSICS_AWAKE));
		bridge.back()->SetImage(black);
		if (i!= 1) { geareng->CreateGearRopeJoint(bridge[i-2], bridge[i-1], 30, 10, 1); }
	}
	geareng->CreateGearRopeJoint(bridge[0],lhinge, 25, 20, 1);
	geareng->CreateGearRopeJoint(bridge[19], rhinge, 25, 20, 1);
}

void CityMap::Render()
{
	background->Render(0, 0);
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
