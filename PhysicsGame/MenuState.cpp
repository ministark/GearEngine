#include "MenuState.h"

MenuState* MenuState::inst = NULL;

MenuState::MenuState(GearEngine* eng)
{
	geareng = eng;
	InputCallBack = 0;
	UpdateCallBack = 0;
	RenderCallBack = 0;
	Init();
}


MenuState * MenuState::GetInstance(GearEngine * eng)
{
	if (!inst) {
		inst = new MenuState(eng);
	}
	return inst;
}

MenuState::~MenuState()
{
	delete inst;
}

void MenuState::Init()
{
	bpimg = geareng->CreateSprite(300, 100, "Image/Buttons/Play.png");
	bplay = new Button(GearVector::ZERO, 400, 150, bpimg);

	beimg = geareng->CreateSprite(300, 100, "Image/Buttons/Exit.png");
	bexit = new Button(GearVector(0, -200), 400, 150, beimg);

}

void MenuState::Cleanup()
{
	bpimg->Remove();
	delete bplay;
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::InputHandle(MSG *msg)
{
	if (bplay->InputListener(msg)) {
		Gear::StateManager::GetInstance(geareng)->AddState(PlayState::GetInstance(geareng));
	}
	else if (bexit->InputListener(msg) || (msg->message == WM_QUIT) ) {
		Gear::StateManager::GetInstance(geareng)->ClearStack();
	}
}

void MenuState::Update()
{
}

void MenuState::Render()
{
	bplay->Render();
	bexit->Render();
}
