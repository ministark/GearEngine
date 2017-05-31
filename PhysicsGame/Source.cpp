// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include "GameWorld.h"
#include "PlayState.h"
#include <ctime>

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}



bool FrameFunc() {

	return true;
}

bool RenderFunc() {

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
	Gear::StateManager *sm = Gear::StateManager::GetInstance(reng);
	sm->AddState(PlayState::GetInstance(reng));
	while (!sm->RunScene())
	{
		
		//reng->render_frame(PHYSICS_DT);
	}

	// clean up DirectX and COM
	reng->cleanD3D();

}


// this is the main message handler for the program

	