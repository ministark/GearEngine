#include "GameButton.h"
#pragma once

class Button :public GameButton
{
public:
	Button(float, float, float, float, GearSprite*, GearSprite* highlighted = NULL);
	bool InputListener(MSG*) ;
	void Render();
	~Button();
};

