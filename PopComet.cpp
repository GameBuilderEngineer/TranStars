#include "PopComet.h"
#include "Stage.h"

void initializePopComet(ObjStr* popComet)
{
	popComet->m_use = true;
	popComet->onAttract = false;
	popComet->m_scl = { 1.0f,1.0f };
	popComet->m_speed = { 0.0f,0.0f };
	popComet->m_accel = { 0.0f,0.0f };
	popComet->m_attract = { 0.0f,0.0f };
	popComet->m_time = 10000.0f;
	popComet->m_mode = -1;
	popComet->m_rad = 50.0f;
	popComet->m_rect = { 100.0f,100.0f };
	InitImage(&popComet->m_image, NULL, popComet->m_pos.x, popComet->m_pos.y, 100.0f, 100.0f);
	popComet->m_image.renderFlag = false;
}

void updatePopComet(ObjStr* popComet)
{
	popComet->m_time += getFrameTime();
	if (popComet->m_time >= 5.0f)
	{
		ObjStr* o = getCometClass()->dynObjPop();
		if (o != NULL)
			initializeObject(o, 0, CHARA_COMET, popComet->m_pos, 0.0f, NULL, 0);//initializeComet“à‚Å“®“IŠm•Û‚·‚é‚Ì‚ÅObjStr*‚ÍNULL
		popComet->m_time = 0.0f;
	}
}
