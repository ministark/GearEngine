#include "Constants.h"
#pragma once
using namespace Gear;
class GameButton
{
public:
	GameButton();
	virtual bool InputListener(MSG*) = 0;
	virtual void Render() = 0;
	GearVector _pos;
	float width, height;
	bool onFocus;
	GearSprite *img, *himg;
	~GameButton();
};

