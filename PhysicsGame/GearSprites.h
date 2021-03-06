#include <string>

#include "GearSettings.h"
#include "GearVector.h"
#pragma once

namespace Gear {
	class GearSprite
	{
		LPDIRECT3DDEVICE9 d3ddev;
		float width, height;
	public:
		CUSTOMVERTEX vertices[4];
		bool markForDeletion;
		void Remove();
		short indices[6] = { 0,1,2,1,3,2 };
		LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;
		LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;
		IDirect3DTexture9 *g_texture = NULL;
		GearSprite(LPDIRECT3DDEVICE9, float, float, std::string);
		void Render(Gear::GearVector &);
		void RenderShader(Gear::GearVector &);
		void RenderX(Gear::GearVector &, float rx, float ry, float rz, float scalex, float scaley);
		void Clean();
		~GearSprite();
	};
}
