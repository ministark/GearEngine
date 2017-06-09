#include "GameButton.h"
#pragma once
using namespace Gear;
class Button :public GameButton
{
public:
	Button(GearVector &, float, float, GearSprite*, GearSprite* highlighted = NULL);
	bool InputListener(MSG*) ;
	void Render();
	~Button();
};

