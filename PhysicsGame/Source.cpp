// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include "GameWorld.h"
#include "PlayState.h"
#include <ctime>

#define GM gw->main
GameWorld *gw;
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



bool FrameFunc() {
	//// Movement
	//if (GM->ishuman) {
	//	if (gw->ka) { GM->addvx(PLAYER_SENSITIVITY); }
	//	if (gw->kd) { GM->addvx(-PLAYER_SENSITIVITY); }
	//	if (gw->kw && !gw->pkw && fabs(GM->body->vy) < VELOCITY_LOW ) { GM->addvy(PLAYER_JUMP); } //Add grounded condition
	//	//	Bullet Firing
	//	if (gw->mleft && !gw->pmleft) gw->addStar(GM->body->x, GM->body->y, (gw->mx - GM->body->x)*BULLET_SPEED, (gw->my - GM->body->y)*BULLET_SPEED);
	//	//Velocity Restriction
	//	(GM->body->vx > 0) ? GM->body->vx = min(PLAYER_SPEEDX, GM->body->vx) : GM->body->vx = max(-PLAYER_SPEEDX, GM->body->vx);
	//	(GM->body->vy > 0) ? GM->body->vy = min(PLAYER_SPEEDY, GM->body->vy) : GM->body->vy = max(-PLAYER_SPEEDY, GM->body->vy);
	//}
	//else {
	//	if (gw->ka) { gw->main->addvx( PLAYER_FLY); }
	//	if (gw->kd) { gw->main->addvx(-PLAYER_FLY); }
	//	if (gw->kw) { gw->main->addvy( PLAYER_FLY); }
	//	if (gw->ks) { gw->main->addvy(-PLAYER_FLY); }
	//	//Disabling gravity for the Skeleton
	//	GM->addvy(PHYSICS_GRAVITY); 
	//	//Velocity Restriction
	//	(GM->body->vx > 0) ? GM->body->vx = min(PLAYER_FLYX, GM->body->vx) : GM->body->vx = max(-PLAYER_FLYX, GM->body->vx);
	//	(GM->body->vy > 0) ? GM->body->vy = min(PLAYER_FLYY, GM->body->vy) : GM->body->vy = max(-PLAYER_FLYY, GM->body->vy);
	//}


	//if (gw->kshift && !gw->pkshift) GM->ishuman = !GM->ishuman;
	//gw->setPrev();
	return true;
}

bool RenderFunc() {
	//gw->Render();//Displays all objects
	//gw->Clean();//Removes all the killed objects
	return true;
}
// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL, "WindowClass", "Our Direct3D Program",
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	GearEngine *reng = new GearEngine();

	// set up and initialize Direct3D
	srand((int)time(0));
	reng->initD3D(hWnd,FrameFunc,RenderFunc);
	gw = new GameWorld(reng);
	Gear::StateManager *sm = Gear::StateManager::GetInstance();
	sm->AddState(PlayState::GetInstance(reng));
	MSG msg;
	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		//	sm->RunScene(&msg);
		}

		if (msg.message == WM_QUIT)
			break;
		sm->RunScene(&msg);

		//reng->render_frame(PHYSICS_DT);
	}

	// clean up DirectX and COM
	reng->cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int r = 0;
	switch (message)
	{
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		gw->mleft	= 1;
		gw->mx		= (SCREEN_WIDTH / 2)  - GET_X_LPARAM(lParam);
		gw->my		= (SCREEN_HEIGHT / 2) - GET_Y_LPARAM(lParam);
		break;
	case WM_LBUTTONUP:
		gw->mleft = 0;
		ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x41:
			gw->ka = 1;		break;
		case 0x44:
			gw->kd = 1;		break;
		case 0x57:
			gw->kw = 1;		break;
		case 0x53:
			gw->ks = 1;		break;
		case VK_SHIFT:
			gw->kshift = 1;	break;
		case VK_ESCAPE:
			PostQuitMessage(0);	break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 0x41:
			gw->ka = 0;		break;
		case 0x44:
			gw->kd = 0;		break;
		case 0x57:
			gw->kw = 0;		break;
		case 0x53:
			gw->ks = 0;		break;
		case VK_SHIFT:
			gw->kshift = 0;	break;
		case VK_ESCAPE:
			PostQuitMessage(0);	break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);	return 0; 
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

	