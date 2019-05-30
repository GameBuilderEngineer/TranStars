#include "SmallStarFrame.h"

void initializeSmallStarFrame(ObjStr* smallStarFrame)
{
	smallStarFrame->m_use = true;
	smallStarFrame->onAttract = false;
	smallStarFrame->m_scl = { 1.0f,1.0f };
	smallStarFrame->m_speed = { 0.0f,0.0f };
	smallStarFrame->m_accel = { 0.0f,0.0f };
	smallStarFrame->m_attract = { 0.0f,0.0f };
	smallStarFrame->m_time = -1;
	smallStarFrame->m_mode = -1;
	smallStarFrame->m_rad = 50.0f;
	smallStarFrame->m_rect = { 100.0f,100.0f };
	InitImage(&smallStarFrame->m_image, getTexture(textureLoaderNS::COMET01), smallStarFrame->m_pos.x, smallStarFrame->m_pos.y, 100.0f, 100.0f);
}
