#include "StarLine.h"

void initializeStarLine(ObjStr* starLine)
{
	starLine->m_scl = { 1.0f,1.0f };
	starLine->m_speed = { 0.0f,0.0f };
	starLine->m_accel = { 0.0f,0.0f };
	starLine->m_attract = { 0.0f,0.0f };
	starLine->m_time = -1;
	starLine->m_mode = -1;
	starLine->m_rad = 50.0f;
	starLine->m_rect = { 100.0f,100.0f };
	InitImage(&starLine->m_image, getTexture(textureLoaderNS::MAGIC_CIRCLE), starLine->m_pos.x, starLine->m_pos.y, 160.0f, 160.0f);
}