#include "PopComet.h"

void initializePopComet(ObjStr* popComet)
{
	popComet->m_scl = { 1.0f,1.0f };
	popComet->m_speed = { 0.0f,0.0f };
	popComet->m_accel = { 0.0f,0.0f };
	popComet->m_attract = { 0.0f,0.0f };
	popComet->m_time = -1;
	popComet->m_mode = -1;
	popComet->m_rad = 50.0f;
	popComet->m_rect = { 100.0f,100.0f };
	InitImage(&popComet->m_image, getTexture(textureLoaderNS::COMET02), popComet->m_pos.x, popComet->m_pos.y, 100.0f, 100.0f);

}