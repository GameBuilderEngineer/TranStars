#include"PopSmallStar.h"

void initializePopSmallStar(ObjStr* popSmallStar)
{
	popSmallStar->m_use = true;
	popSmallStar->onAttract = false;
	popSmallStar->m_scl = { 1.0f,1.0f };
	popSmallStar->m_speed = { 0.0f,0.0f };
	popSmallStar->m_accel = { 0.0f,0.0f };
	popSmallStar->m_attract = { 0.0f,0.0f };
	popSmallStar->m_time = -1;
	popSmallStar->m_mode = -1;
	popSmallStar->m_rad = 50.0f;
	popSmallStar->m_rect = { 100.0f,100.0f };
	InitImage(&popSmallStar->m_image,getTexture(textureLoaderNS::SMALL_STAR),popSmallStar->m_pos.x, popSmallStar->m_pos.y, 100.0f, 100.0f);
}

void updatePopSmallStar(ObjStr* obj)
{

}