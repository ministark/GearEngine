#include <windows.h>
#include "GearEngine.h"
#pragma once
namespace Gear {
	class State
	{
	public:
		State();
		virtual void Init() = 0;
		virtual void Cleanup() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual State* InputHandle(MSG*) = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		~State();
		bool InputCallBack,UpdateCallBack, RenderCallBack, pause;
		GearEngine* geareng;
	};
}