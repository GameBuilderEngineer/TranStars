
#include "Cursor.h"
#include "input.h"

void initializeCursor(ObjStr* cursor)
{
	cursor->onAttract = false;
	cursor->m_scl = { 1.0f,1.0f };
	cursor->m_speed = { 0.0f,0.0f };
	cursor->m_accel = { 0.0f,0.0f };
	cursor->m_attract = { 0.0f,0.0f };
	cursor->m_time = -1;
	cursor->m_mode = -1;
	cursor->m_rad = 50.0f;
	cursor->m_rect = { 100.0f,100.0f };
	InitImage(&cursor->m_image, getTexture(textureLoaderNS::MAGIC_CIRCLE), cursor->m_pos.x, cursor->m_pos.y, 160.0f, 160.0f);

}

void updateCursor(ObjStr* cursor)
{
	if (getMouseLButtonTrigger() || getMouseRButtonTrigger()) {
		cursor->m_pos = { (float)getMouseX() - 40.0f, (float)getMouseY() - 40.0f };
		cursor->m_pos.y += cursor->m_image.height;
		cursor->m_image.height = 0.0f;

		setAngle(&cursor->m_image, 0.0f);
	}
	if ((cursor->m_image.height < cursor->m_image.width)) {
		cursor->m_pos.y -= (float)cursor->m_image.width / 25.0f;
		cursor->m_image.height += (float)cursor->m_image.width / 25.0f;

		cursor->m_image.angle -= 2.0f;//‰ñ“]‚Ì‘ŠŽE
	}
	else {
		cursor->m_pos = { (float)getMouseX() - 40.0f, (float)getMouseY() - 40.0f };
		cursor->m_image.height = cursor->m_image.width;
	}

}