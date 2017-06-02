#include "Button.h"



Button::Button(float xpos, float ypos, float w, float h, GearSprite *image , GearSprite * highlighted)
{
	x = xpos; y = ypos; width = w; height = h; 
	img = image;  	(highlighted == NULL) ? himg = img : himg = highlighted;
	onFocus = 0;
}

bool Button::InputListener(MSG *msg)
{
	switch (msg->message)
	{
	case WM_LBUTTONDOWN:
		SetCapture(msg->hwnd);
		if (onFocus) {
			return true;
		}
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		float mouse_x = (float)((SCREEN_WIDTH / 2) - GET_X_LPARAM(msg->lParam));
		float mouse_y = (float)((SCREEN_HEIGHT / 2) - GET_Y_LPARAM(msg->lParam));
		onFocus = (fabs(mouse_x - x) < width / 2 && fabs(mouse_y - y) < height / 2) ? 1 : 0;
		break;
	}
	DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
	return false;
}

void Button::Render()
{
	(onFocus) ? himg->RenderX(x,y,0,0,0,ONFOCUS_SCALE,  ONFOCUS_SCALE): img->Render(x, y);
}


Button::~Button()
{
}
