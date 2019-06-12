#include "PopComet.h"
#include <vector>
#include "comet.h"

float popTimeComet = 0;

std::vector<ObjStr> comet;

void initializePopComet(ObjStr* popComet)
{
	popComet->m_use = true;
	popComet->onAttract = false;
	popComet->m_scl = { 1.0f,1.0f };
	popComet->m_speed = { 0.0f,0.0f };
	popComet->m_accel = { 0.0f,0.0f };
	popComet->m_attract = { 0.0f,0.0f };
	popComet->m_time = -1;
	popComet->m_mode = -1;
	popComet->m_rad = 50.0f;
	popComet->m_rect = { 100.0f,100.0f };
	InitImage(&popComet->m_image, NULL, popComet->m_pos.x, popComet->m_pos.y, 100.0f, 100.0f);
	popComet->m_image.renderFlag = false;
}

void updatePopComet(ObjStr* popComet)
{
	popTimeComet += getFrameTime();
	if (popTimeComet >= 1.0f)
	{
		ObjStr data;

		initializeComet(&data,01,CHARA_COMET,popComet->m_pos,0);
		comet.push_back(data);
		popTimeComet = 0;
	}

	for (ObjStr i : comet)
	{
		updateObject(&i);
	}
}

void drawComet()
{
	for (ObjStr i : comet)
	{
		drawObject(&i);
	}	
}

