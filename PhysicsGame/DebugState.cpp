#include "DebugState.h"


DebugState* DebugState::inst = NULL;

DebugState * DebugState::GetInstance(GearEngine *eng)
{
	if (!inst) {
		inst = new DebugState(eng);
	}
	return inst;
}

void DebugState::ResetInstance()
{
	Init();
}

DebugState::DebugState(GearEngine *eng)
{
	geareng = eng;
	InputCallBack = 0;
	RenderCallBack = 0;
	UpdateCallBack = 0;
	Init();
}


DebugState::~DebugState()
{
	Cleanup();
}


void DebugState::Init()
{
	main = new Protagonist(geareng);
}

void DebugState::Cleanup()
{
}

void DebugState::Pause()
{
	pause = 1;
}

void DebugState::Resume()
{
	pause = 0;
}

void DebugState::InputHandle(MSG * msg)
{
	switch (msg->message)
	{
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

void DebugState::Update()
{
}

void DebugState::Render()
{
	main->Render();
}
