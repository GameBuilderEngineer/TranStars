
#include "Cursor.h"

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

}