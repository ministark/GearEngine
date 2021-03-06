#include "PlayState.h"


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
	map = new CityMap(geareng);
	map->Init();

	//Set the Player and AI
	main = new Protagonist(geareng);
	///foe = new Foe(geareng);
	//geareng->CreateGearDistanceJointX(main->body,foe->body , 200, 10, 0);
	//geareng->CreateGearDistanceJoint(main->body, foe->body, 200, 10, 0);
	//geareng->CreateGearRopeJoint(main->body, foe->body, 400, 100, 10);
	efac = new FoeFactory(geareng, main);
	efac->addEnemy();
	key_w = 0; key_a = 0; key_s = 0; key_d = 0; key_shift = 0; mouse_l = 0; mouse.clear();
	pkey_w = 0; pmouse_l = 0; pkey_shift = 0;
}

void PlayState::Cleanup()
{
	delete map;
	delete main;
	//delete foe;
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
		mouse._x = (float)((SCREEN_WIDTH / 2)	-	GET_X_LPARAM(msg->lParam));
		mouse._y = (float)((SCREEN_HEIGHT / 2)	-	GET_Y_LPARAM(msg->lParam));
		break;
	case WM_LBUTTONUP:
		mouse_l = 0;
		ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		mouse._x = (float)((SCREEN_WIDTH / 2) - GET_X_LPARAM(msg->lParam));
		mouse._y = (float)((SCREEN_HEIGHT / 2) - GET_Y_LPARAM(msg->lParam));
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
	main->Update();
	if (main->ishuman) {
		if (key_a) { main->addvx(PLAYER_SENSITIVITY); }
		if (key_d) { main->addvx(-PLAYER_SENSITIVITY); }
		if (key_w && !pkey_w /*&& fabs(main->body->vy) < VELOCITY_LOW*/ && main->isGrounded) { main->addvy(PLAYER_JUMP); } 
		if (mouse_l && !pmouse_l) {
			stars.push_back(new Projectile(geareng, main->body->_pos, (mouse- main->body->_pos)*BULLET_SPEED));
			main->body->_vel -= (mouse - main->body->_pos)*BULLET_SPEED*PLAYER_RECOIL;
		} 
		//Velocity Restriction of moving
		 (main->body->_vel._x>0) ? main->body->_vel._x = min(PLAYER_SPEEDX, main->body->_vel._x):main->body->_vel._x = max(-PLAYER_SPEEDX, main->body->_vel._x);
		 (main->body->_vel._y > 0) ? main->body->_vel._y = min(PLAYER_SPEEDY, main->body->_vel._y) : main->body->_vel._y = max(-PLAYER_SPEEDY, main->body->_vel._y);
	}
	else {
		if (key_a) { main->addvx(PLAYER_FLY); }
		if (key_d) { main->addvx(-PLAYER_FLY); }
		if (key_w) { main->addvy(PLAYER_FLY); }
		if (key_s) { main->addvy(-PLAYER_FLY); }

		//Disabling gravity for the Skeleton
		main->addvy(PHYSICS_GRAVITY);

		//Velocity Restriction of Flying
		(main->body->_vel._x > 0) ? main->body->_vel._x = min(PLAYER_FLYX, main->body->_vel._x) : main->body->_vel._x = max(-PLAYER_FLYX, main->body->_vel._x);
		(main->body->_vel._y > 0) ? main->body->_vel._y = min(PLAYER_FLYY, main->body->_vel._y) : main->body->_vel._y = max(-PLAYER_FLYY, main->body->_vel._y);
	}
	if (key_shift && !pkey_shift) main->ishuman = !main->ishuman;
	
	//Add force to the bullet
	if (!main->ishuman) {
		for (auto ite = stars.begin(); ite != stars.end(); ++ite) {
			(*ite)->body->_vel += (mouse - (*ite)->body->_pos)*BULLET_REPOS;
		}
	}
	//Set the previous value
	pkey_w = key_w; pkey_shift = key_shift; pmouse_l = mouse_l;

	//Let the AI Play
	efac->UpdateAI(stars);

	//Time step could be introduced here
	geareng->PhysicsEngine(PHYSICS_DT);
}

void PlayState::Render()
{
	map->Render();
	main->Render();
	//foe->Render();
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
	Cleanup();
}

