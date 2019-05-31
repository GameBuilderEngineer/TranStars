
#include "comet.h"
#include "effect.h"
#include "Stage.h"

void initializeComet(ObjStr* comet)
{
	comet->m_use = true;
	comet->onAttract = false;
	comet->m_scl = { 1.0f,1.0f };
	comet->m_speed = { 0.0f,0.0f };
	comet->m_accel = { 0.0f,0.0f };
	comet->m_attract = { 0.0f,0.0f };
	comet->m_time = -1;
	comet->m_mode = -1;
	comet->m_rad = 50.0f;
	comet->m_rect = { 100.0f,100.0f };
	InitImage(&comet->m_image, getTexture(textureLoaderNS::COMET01), comet->m_pos.x, comet->m_pos.y, 100.0f, 100.0f);
}

void updateComet(ObjStr* comet)
{
	makeEffect(getEffect(), eTAIL, comet);//êºêÏ0531
}