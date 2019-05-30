#include "StarDust.h"

void initializeStarDust(ObjStr* starDust)
{
	starDust->m_scl = { 1.0f,1.0f };
	starDust->m_speed = { 0.0f,0.0f };
	starDust->m_accel = { 0.0f,0.0f };
	starDust->m_attract = { 0.0f,0.0f };
	starDust->m_time = -1;
	starDust->m_mode = -1;
	starDust->m_rad = 50.0f;
	starDust->m_rect = { 100.0f,100.0f };
	InitAnimeImage(&starDust->m_image, getTexture(textureLoaderNS::BACK_GROUND), starDust->m_pos.x, starDust->m_pos.y, 160.0f, 80.0f, 3, 5, 10, 5);
}
