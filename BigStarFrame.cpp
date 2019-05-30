
#include "BIgStarFrame.h"

void initializeBigStarFrame(ObjStr* bigStarFrame)
{
	bigStarFrame->m_use = true;
	bigStarFrame->onAttract = false;
	bigStarFrame->m_scl = { 1.0f,1.0f };
	bigStarFrame->m_speed = { 0.0f,0.0f };
	bigStarFrame->m_accel = { 0.0f,0.0f };
	bigStarFrame->m_attract = { 0.0f,0.0f };
	bigStarFrame->m_time = -1;
	bigStarFrame->m_mode = -1;
	bigStarFrame->m_rad = 50.0f;
	bigStarFrame->m_rect = { 100.0f,100.0f };
	InitImage(&bigStarFrame->m_image, getTexture(textureLoaderNS::WALL), bigStarFrame->m_pos.x, bigStarFrame->m_pos.y, 40.0f, 300.0f);
}
