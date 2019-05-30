#include"PopStar.h"
#include "main.h"

void initializePopStar(ObjStr* popStar)
{
	popStar->m_use = true;
	popStar->onAttract = false;
	popStar->m_scl = { 1.0f,1.0f };
	popStar->m_speed = { 0.0f,0.0f };
	popStar->m_accel = { 0.0f,0.0f };
	popStar->m_attract = { 0.0f,0.0f };
	popStar->m_time = -1;
	popStar->m_mode = -1;
	popStar->m_rad = 50.0f;
	popStar->m_rect = { 100.0f,100.0f };
	InitImage(&popStar->m_image,NULL,popStar->m_pos.x, popStar->m_pos.y, 100.0f, 100.0f);
}

void updatePopStar(ObjStr* popStar)
{
	getFrameTime();
}