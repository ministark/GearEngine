#include "Constants.h"
#pragma once
class GameButton
{
public:
	GameButton();
	virtual bool InputListener(MSG*) = 0;
	virtual void Render() = 0;
	float x, y, width, height;
	bool onFocus;
	GearSprite *img, *himg;
	~GameButton();
};

