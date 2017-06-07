// Standard Libraries
#include <vector>
#include <list>

// Custom Libraries
#include "GearSettings.h"
#include "GearSprites.h"
#include "GearPhysicsBody.h"
#include "GearJoint.h"
#include "GearDistanceJointX.h"
#include "GearDistanceJointY.h"
#include "GearDistanceJoint.h"
#include "GearRopeJoint.h"
#include "GearQuadTree.h"
#pragma once


class GearEngine
{

	LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
	IDirect3DTexture9 *g_texture = NULL;
	GearSprite* tri;
	bool (*FrameFunc)(), (*RenderFunc)();
	std::list<GearSprite*> *sprites;
	std::list<GearPhysicsBody*> *pbodies;
	std::list<GearJoint*> *joints;
	Gear::GearQuadTree* quad_tree;
public:
	GearEngine();
	void initD3D(HWND hWnd, bool (*)(), bool (*)());    // sets up and initializes Direct3D
	void InitRender();
	void CleanRender();
	void render_frame(float dt);    // renders a single frame
	GearSprite* CreateSprite(float,float,std::string);
	GearPhysicsBody* CreatePhysicsBody(float, float, float, float, float, float, float,float, int);
	GearJoint* CreateGearDistanceJointX(GearPhysicsBody*, GearPhysicsBody*, float, float, float);
	GearJoint* CreateGearDistanceJointY(GearPhysicsBody*, GearPhysicsBody*, float, float, float);
	GearJoint* CreateGearDistanceJoint(GearPhysicsBody*, GearPhysicsBody*, float, float, float);
	GearJoint* CreateGearRopeJoint(GearPhysicsBody*, GearPhysicsBody*, float, float,float);

	void PhysicsEngine(float);
	void PhysicsEngineX(float); //Faster Implementation
	void Kinematics(float);
	void cleanD3D(void);    // closes Direct3D and releases memory
	~GearEngine();
};

