#include "GearEngine.h"
using namespace Gear;


GearEngine::GearEngine()
{
}

void GearEngine::initD3D(HWND hWnd,bool (*ff)(),bool (*rf)())
{
	FrameFunc = ff; RenderFunc = rf;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH; d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&d3ddev);

	sprites = new std::list<GearSprite*>();
	pbodies = new std::list<GearPhysicsBody*>();
	joints = new std::list<GearJoint*>();

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);    // turn off the 3D lighting

	quad_tree = new Gear::GearQuadTree( 0, GearVector(-SCREEN_WIDTH, -SCREEN_HEIGHT), GearVector( SCREEN_WIDTH, SCREEN_HEIGHT) );
}

void GearEngine::InitRender()
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	d3ddev->BeginScene();

	// Setting the Camera
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(CAMERA_POSX, CAMERA_POSY, CAMERA_POSZ),    // the camera position
		&D3DXVECTOR3(CAMERA_FACEX, CAMERA_FACEY, CAMERA_FACEZ),    // the look-at position
		&D3DXVECTOR3(CAMERA_UPX, CAMERA_UPY, CAMERA_POSZ));    // the up direction
	d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

												   // Setting Orthogonal Projection
	D3DXMATRIX matProj;
	D3DXMatrixOrthoLH(&matProj, SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f);
	d3ddev->SetTransform(D3DTS_PROJECTION, &matProj);
}

void GearEngine::CleanRender()
{
	// End Scene
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);

	// Delete all the marked Object
	std::list<GearSprite*>::iterator ite1 = sprites->begin();
	while (ite1 != sprites->end()) {
		if ((*ite1)->markForDeletion) { delete (*ite1); ite1 = sprites->erase(ite1); }
		else ++ite1;
	}
	std::list<GearPhysicsBody*>::iterator ite2 = pbodies->begin();
	while (ite2 != pbodies->end()) {
		if ((*ite2)->markForDeletion) { delete (*ite2); ite2 = pbodies->erase(ite2); }
		else ++ite2;
	}

}

void GearEngine::render_frame(float dt)
{	
	// Let Game Process and Physics Engine work
	FrameFunc();
	PhysicsEngine(dt);
	InitRender();

	// Let Game render the sprites
	RenderFunc();
	CleanRender();
	
}

void GearEngine::cleanD3D(void)
{
	// Clear all the Vertex buffer
	for (std::list<GearSprite*>::iterator ite = sprites->begin(); ite != sprites->end();ite++) (*ite)->Clean();
	// Release the device
	d3ddev->Release();
	// Release the Direct3D
	d3d->Release();	
}


GearSprite * GearEngine::CreateSprite(float w, float h, std::string image)
{
	sprites->push_back(new GearSprite(d3ddev,w,h,image));
	return sprites->back();
}

GearPhysicsBody * GearEngine::CreatePhysicsBody(GearVector &pos, GearVector &vel, float width, float height, float invm,float e, int state)
{
	pbodies->push_back(new GearPhysicsBody(pos, vel, width, height, invm, e, state));
	return pbodies->back();
}

GearJoint * GearEngine::CreateGearDistanceJointX(GearPhysicsBody *b1, GearPhysicsBody *b2, float d, float s, float damp)
{
	joints->push_back(new GearDistanceJointX(b1, b2, d, s, damp));
	return joints->back();
}

GearJoint * GearEngine::CreateGearDistanceJointY(GearPhysicsBody *b1, GearPhysicsBody *b2, float d, float s, float damp)
{
	joints->push_back(new GearDistanceJointY(b1, b2, d, s, damp));
	return joints->back();
}

GearJoint * GearEngine::CreateGearDistanceJoint(GearPhysicsBody *b1, GearPhysicsBody *b2, float dist, float stiff, float damp)
{
	joints->push_back(new GearDistanceJoint(b1, b2, dist, stiff, damp));
	return joints->back();
}

GearJoint * GearEngine::CreateGearRopeJoint(GearPhysicsBody *b1, GearPhysicsBody *b2, float d, float stiff, float damp)
{
	joints->push_back(new GearRopeJoint(b1, b2, d, stiff, damp));
	return joints->back();
}

// Physics of the world moves ahead by dt step
void GearEngine::PhysicsEngine(float dt)
{
	Kinematics(dt);
	//Check for constraints
	for (std::list<GearJoint*>::iterator ite = joints->begin(); ite != joints->end(); ++ite) {
		(*ite)->ResolveConstraint();
	}

	//Check for collisions
	for (std::list<GearPhysicsBody*>::iterator ite = pbodies->begin(); ite != pbodies->end(); ++ite) {
		if ((*ite)->state != PHYSICS_STATIC )(*ite)->_vel._y -= PHYSICS_GRAVITY;
		std::list<GearPhysicsBody*>::iterator nite = ite; ++nite;
		while (nite != pbodies->end()) {
			if ( (*ite)->state == PHYSICS_AWAKE || (*nite)->state == PHYSICS_AWAKE) {
				GearVector normal = (*ite)->Collide((*nite)); float min_e = min((*ite)->e, (*nite)->e);
				float pen = normal.norm();
				float velnorm = normal*((*nite)->_vel - (*ite)->_vel);
				if (!normal.zero() && velnorm <= 0) {
					// Penetration correction
					GearVector corr = normal*(max(pen - PHYSICS_SLOP, 0.0f) * PHYSICS_PEN / ((*nite)->invmass + (*ite)->invmass));
					(*ite)->_pos -= corr*(*ite)->invmass; (*nite)->_pos += corr*(*nite)->invmass;
					//Collison resolve
					float j = (1.0f + min_e) * (-velnorm) / ((*nite)->invmass + (*ite)->invmass);
					GearVector impulse = normal * j;
					(*ite)->_vel -= impulse*(*ite)->invmass;	if ((*ite)->state != PHYSICS_STATIC) (*ite)->state = PHYSICS_AWAKE;
					(*nite)->_vel += impulse*(*nite)->invmass;	if ((*nite)->state != PHYSICS_STATIC) (*nite)->state = PHYSICS_AWAKE;
					if ((*ite)->OnCollision != 0)	 (*ite)->OnCollision((void*)(*ite), (void*)(*nite));
					if ((*nite)->OnCollision != 0)	(*nite)->OnCollision((void*)(*nite), (void*)(*ite));
				}
			}
			++nite;
		}
	}
}

void GearEngine::PhysicsEngineX(float dt)
{
	Kinematics(dt);
	
	//Check for constraints
	for (std::list<GearJoint*>::iterator ite = joints->begin(); ite != joints->end(); ++ite) {
		(*ite)->ResolveConstraint();
	}

	//Add the bodies to the quad tree;
	quad_tree->clear();
	for (auto ite = pbodies->begin(); ite != pbodies->end(); ++ite) 
		quad_tree->insert((*ite));
	quad_tree->solve();

}

void GearEngine::Kinematics(float dt)
{
	for (std::list<GearPhysicsBody*>::iterator ite = pbodies->begin(); ite != pbodies->end(); ++ite) {
		if ((*ite)->state != PHYSICS_STATIC) {
			if ((*ite)->_vel.len() > PHYSICS_VMIN) {
				(*ite)->_pos += (*ite)->_vel*dt;
			}
		}
		else {
			(*ite)->_vel.clear();
		}
	}
}


GearEngine::~GearEngine()
{
}
