#include "BigStar.h"


void initializeBigStar(ObjStr* bigStar)
{
	bigStar->m_use = true;
	bigStar->onAttract = true;
	bigStar->m_speed.x = -1.0f;
	bigStar->m_scl = { 1.0f,1.0f };
	bigStar->m_speed = { 0.0f,0.0f };
	bigStar->m_accel = { 1.0f,0.0f };
	bigStar->m_attract = { 0.0f,0.0f };
	bigStar->m_time = -1;
	bigStar->m_mode = -1;
	bigStar->m_rad = 50.0f;
	bigStar->m_rect = { 100.0f,100.0f };
	InitImage(&bigStar->m_image, getTexture(textureLoaderNS::BIG_STAR), bigStar->m_pos.x, bigStar->m_pos.y, 50.0f, 50.0f);
}

void updateBigStar(ObjStr* bigStar)
{

}