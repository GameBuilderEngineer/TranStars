#include "PopBigStar.h"

void initializePopBigStar(ObjStr* popBigStar)
{
	popBigStar->m_scl = { 1.0f,1.0f };
	popBigStar->m_speed = { 0.0f,0.0f };
	popBigStar->m_accel = { 0.0f,0.0f };
	popBigStar->m_attract = { 0.0f,0.0f };
	popBigStar->m_time = -1;
	popBigStar->m_mode = -1;
	popBigStar->m_rad = 50.0f;
	popBigStar->m_rect = { 100.0f,100.0f };
	InitImage(&popBigStar->m_image, getTexture(textureLoaderNS::BIG_STAR), popBigStar->m_pos.x, popBigStar->m_pos.y, 100.0f, 100.0f);
}

