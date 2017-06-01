#include "PlayState.h"

using namespace Gear;

PlayState* PlayState::inst = NULL;



PlayState::PlayState(GearEngine* eng)
{
	geareng = eng;
	InputCallBack = 0;
	RenderCallBack = 0;
	UpdateCallBack = 0;
	Init();
}

void PlayState::Init()
{
	//Set the enviornment
	background = geareng->CreateSprite(SCREEN_WIDTH, SCREEN_HEIGHT, "Image/Background/LensFlare2.png");
	sun = geareng->CreateSprite(518, 659, "Image/Background/Sun.png");

	edges = new Walls(geareng);
	//Set the Player and AI
	main = new Protagonist(geareng);
	foe = new Foe(geareng);
	//geareng->CreateGearDistanceJointX(main->body,foe->body , 200, 10, 0);
	//geareng->CreateGearDistanceJoint(main->body, foe->body, 200, 10, 0);
	//geareng->CreateGearRopeJoint(main->body, foe->body, 400, 100, 10);
	efac = new FoeFactory(geareng);
	efac->addEnemy(geareng);
	key_w = 0; key_a = 0; key_s = 0; key_d = 0; key_shift = 0; mouse_l = 0; mouse_x = 0; mouse_y = 0;
	pkey_w = 0; pmouse_l = 0; pkey_shift = 0;
}

void PlayState::Cleanup()
{
	background->Remove();
	sun->Remove();
	delete edges;
	delete main;
	delete foe;
	delete efac;
}

void PlayState::Pause()
{
	pause = 1;
}

void PlayState::Resume()
{
	pause = 0;
}

void PlayState::InputHandle(MSG* msg)
{
	switch (msg->message)
	{
	case WM_LBUTTONDOWN:
		SetCapture(msg->hwnd);
		mouse_l = 1;
		mouse_x = (float)((SCREEN_WIDTH / 2)	-	GET_X_LPARAM(msg->lParam));
		mouse_y = (float)((SCREEN_HEIGHT / 2)	-	GET_Y_LPARAM(msg->lParam));
		break;
	case WM_LBUTTONUP:
		mouse_l = 0;
		ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		mouse_x = (float)((SCREEN_WIDTH / 2) - GET_X_LPARAM(msg->lParam));
		mouse_y = (float)((SCREEN_HEIGHT / 2) - GET_Y_LPARAM(msg->lParam));
		break;
	case WM_KEYDOWN:
		switch (msg->wParam)
		{
		case 0x41:
			key_a = 1;		break;
		case 0x44:
			key_d = 1;		break;
		case 0x57:
			key_w = 1;		break;
		case 0x53:
			key_s = 1;		break;
		case VK_SHIFT:
			key_shift = 1;	break;
		case VK_ESCAPE:
			StateManager::GetInstance(geareng)->AddState(PauseState::GetInstance(geareng));
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg->wParam)
		{
		case 0x41:
			key_a = 0;		break;
		case 0x44:
			key_d = 0;		break;
		case 0x57:
			key_w = 0;		break;
		case 0x53:
			key_s = 0;		break;
		case VK_SHIFT:
			key_shift = 0;	break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_QUIT:
		StateManager::GetInstance(geareng)->ClearStack();
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
}

void PlayState::Update()
{
	if (main->ishuman) {
		if (key_a) { main->addvx(PLAYER_SENSITIVITY); }
		if (key_d) { main->addvx(-PLAYER_SENSITIVITY); }
		if (key_w && !pkey_w && fabs(main->body->vy) < VELOCITY_LOW) { main->addvy(PLAYER_JUMP); } //Add grounded condition
																								   //	Bullet Firing
		if (mouse_l && !pmouse_l) {
			stars.push_back(new Projectile(geareng, main->body->x, main->body->y, (mouse_x - main->body->x)*BULLET_SPEED, (mouse_y - main->body->y)*BULLET_SPEED));
			main->addvx(-(mouse_x - main->body->x)*BULLET_SPEED*PLAYER_RECOIL);
			main->addvy(-(mouse_y - main->body->y)*BULLET_SPEED*PLAYER_RECOIL);
		} /*main->addStar(main->body->x, main->body->y, (gw->mx - main->body->x)*BULLET_SPEED, (gw->my - main->body->y)*BULLET_SPEED);*/
		//Velocity Restriction
		 (main->body->vx > 0) ? main->body->vx = min(PLAYER_SPEEDX, main->body->vx) : main->body->vx = max(-PLAYER_SPEEDX, main->body->vx);
		 (main->body->vy > 0) ? main->body->vy = min(PLAYER_SPEEDY, main->body->vy) : main->body->vy = max(-PLAYER_SPEEDY, main->body->vy);
	}
	else {
		if (key_a) { main->addvx(PLAYER_FLY); }
		if (key_d) { main->addvx(-PLAYER_FLY); }
		if (key_w) { main->addvy(PLAYER_FLY); }
		if (key_s) { main->addvy(-PLAYER_FLY); }
		//Disabling gravity for the Skeleton
		main->addvy(PHYSICS_GRAVITY);
		//Velocity Restriction
		(main->body->vx > 0) ? main->body->vx = min(PLAYER_FLYX, main->body->vx) : main->body->vx = max(-PLAYER_FLYX, main->body->vx);
		(main->body->vy > 0) ? main->body->vy = min(PLAYER_FLYY, main->body->vy) : main->body->vy = max(-PLAYER_FLYY, main->body->vy);
	}
	if (key_shift && !pkey_shift) main->ishuman = !main->ishuman;
	
	//Add force to the bullet
	for (auto ite = stars.begin(); ite != stars.end(); ++ite) {
		(*ite)->body->vx += (mouse_x - (*ite)->body->x)*BULLET_REPOS;
		(*ite)->body->vy += (mouse_y - (*ite)->body->y)*BULLET_REPOS;
	}


	//Set the previous value
	pkey_w = key_w; pkey_shift = key_shift; pmouse_l = mouse_l;

	//Time step could be introduced here
	geareng->PhysicsEngine(PHYSICS_DT);
}

void PlayState::Render()
{
	background->Render(0,0);
	//sun->Render(350 + (main->body->x)*0.1, 100);
	
	main->Render();
	foe->Render();
	efac->Render();
	for (std::list<Projectile*>::iterator ite = stars.begin(); ite != stars.end(); ite++) {
		(*ite)->Render();
	}


	//Remove stars
	std::list<Projectile*>::iterator ite = stars.begin();
	while (ite != stars.end()) {
		if ((*ite)->dead || (*ite)->outOfScreen()) {
			(*ite)->body->Remove();
			delete (*ite); //Free the heap
			ite = stars.erase(ite);
		}
		else  ite++;
	}
	efac->Clean();

	//Clear all the deleted physicsbody
	//StateManager *inst = StateManager::GetInstance();
}

PlayState* PlayState::GetInstance(GearEngine* eng)
{
	if (!inst) {
		inst = new PlayState(eng);
	}
	return inst;
}

void PlayState::ResetInstance()
{
	Init();
}


PlayState::~PlayState()
{
}

