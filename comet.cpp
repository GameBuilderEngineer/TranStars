#include "comet.h"
#include "Stage.h"

//•’Ê‚ÌŠÖ”

void initializeComet(ObjStr* comet)
{
	comet->m_id = short(getCometClass()->getDynObjNum() - 1);
	comet->m_use = true;
	comet->onAttract = true;
	comet->m_scl = { 1.0f,1.0f };
	comet->m_speed = { cosf(comet->m_rot),sinf(comet->m_rot) };
	comet->m_accel = { 0.0f,0.0f };
	comet->m_attract = { 0.0f,0.0f };
	comet->m_time = -1.0f;
	comet->m_mode = -1;
	comet->m_rad = 50.0f;
	comet->m_rect = { 100.0f,100.0f };
	InitImage(&comet->m_image, getTexture(textureLoaderNS::COMET01), comet->m_pos.x, comet->m_pos.y, 100.0f, 100.0f);
}

void updateComet(ObjStr* comet)
{
	if (comet->m_use)
		makeEffect(getEffect(), eTAIL, comet);//¼ì0531
}