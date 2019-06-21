#include "SmallStar.h"
#include "Stage.h"

void initializeSmallStar(ObjStr* smallStar)
{
	smallStar->m_id = short(getStarClass()->getDynObjNum() - 1);
	smallStar->m_use = true;
	smallStar->onAttract = true;
	smallStar->m_speed.x = -1.0f;
	smallStar->m_scl = { 1.0f,1.0f };
	smallStar->m_speed = { 0.0f,0.0f };
	smallStar->m_accel = { 1.0f,0.0f };
	smallStar->m_attract = { 1.0f,0.0f };
	smallStar->m_time = -1.0f;
	smallStar->m_mode = -1;
	smallStar->m_rad = 50.0f;
	smallStar->m_rect = { 100.0f,100.0f };
	InitImage(&smallStar->m_image, getTexture(textureLoaderNS::SMALL_STAR), smallStar->m_pos.x, smallStar->m_pos.y, 50.0f, 50.0f);
}

void updateSmallStar(ObjStr* smallStar)
{
	
}
