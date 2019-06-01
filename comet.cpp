
#include "comet.h"
#include "effect.h"
#include "Stage.h"

void initializeComet(ObjStr* comet, int id, int objType, VECTOR2 position, float angle)
{
	comet->m_pos = position;
	comet->m_id = id;
	comet->m_type = (objTypes)objType;
	comet->m_rot = angle;
	comet->m_use = true;
	comet->onAttract = true;
	comet->m_scl = { 1.0f,1.0f };
	comet->m_speed = { 0.0f,0.0f };
	comet->m_accel = { 15.0f,10.0f };
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