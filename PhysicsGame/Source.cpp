// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include "MenuState.h"
#include <ctime>

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_CLOSE) {
		PostQuitMessage(0);
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	srand((int)time(0));
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

	hWnd = CreateWindowEx(NULL, "WindowClass", "PhysicsGame",
		WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	// Game Engine
	Gear::GearEngine *reng = new Gear::GearEngine();
	reng->initD3D(hWnd,NULL,NULL);
	
	// State manager
	Gear::StateManager *sm = Gear::StateManager::GetInstance(reng);
	
	//Add the Scene
	sm->AddState(MenuState::GetInstance(reng));
	
	// Game Loop
	while (!sm->RunScene()) {}
	
	reng->cleanD3D();

}


	