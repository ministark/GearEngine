#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#pragma once

// Screen Settings
	#define SCREEN_WIDTH		1920
	#define SCREEN_HEIGHT		1080

// States of Physics Objects
	#define PHYSICS_AWAKE		1
	#define PHYSICS_SLEEP		2
	#define PHYSICS_STATIC		3

// Physics Thresholds
	#define PHYSICS_VMIN		0.01
	#define PHYSICS_VMAX		10 
	#define PHYSICS_DT			0.05f
	#define PHYSICS_FREEZE		10
	#define PHYSICS_GRAVITY		0//5.0f	
	#define PHYSICS_PEN			0.6f
	#define PHYSICS_SLOP		0.1f

// Camera Settings
	#define CAMERA_POSX			0.0f
	#define CAMERA_POSY			0.0f
	#define CAMERA_POSZ			20.0f
	#define	CAMERA_FACEX		0.0f
	#define	CAMERA_FACEY		0.0f
	#define	CAMERA_FACEZ		0.0f
	#define CAMERA_UPX			0.0f
	#define CAMERA_UPY			1.0f
	#define CAMERA_UPZ			0.0f
// Vertex used in the engine
	#define CUSTOMFVF (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1)
	#define CUSTOMFVF2 (D3DFVF_XYZ|D3DFVF_DIFFUSE)

struct CUSTOMVERTEX { FLOAT X, Y, Z;D3DCOLOR COLOR; FLOAT U, V; };
struct CUSTOMVERTEX2 { float x, y, z; DWORD color;};

#pragma once
