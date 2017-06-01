#include "PauseState.h"
using namespace Gear;

PauseState* PauseState::inst = NULL;



PauseState::PauseState(GearEngine* eng)
{
	geareng = eng;
	InputCallBack = 0;
	UpdateCallBack = 0;
	RenderCallBack = 1;
	Init();
}


void PauseState::Init()
{
	pauseimg = geareng->CreateSprite(653, 191, "Image/Background/Pause2.png");

}

PauseState::~PauseState()
{
}

PauseState * PauseState::GetInstance(GearEngine *eng)
{
	if (!inst) {
		inst = new PauseState(eng);
	}
	return inst;
}


void PauseState::Cleanup()
{
}

void PauseState::Pause()
{
}

void PauseState::Resume()
{
}

void PauseState::InputHandle(MSG *msg)
{
	switch (msg->message) 
	{
	case WM_KEYDOWN: 
		if (msg->wParam == VK_ESCAPE) {
			StateManager::GetInstance(geareng)->RemoveState();
		}
		break;
	case WM_QUIT:
		StateManager::GetInstance(geareng)->ClearStack();
		break;
	}
	DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
}

void PauseState::Update()
{
}

void PauseState::Render()
{
	pauseimg->Render(0,0);
}
