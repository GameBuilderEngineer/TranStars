#include "Reflection.h"

void initializeReflection(ObjStr* reflection)
{
	reflection->m_use = true;
	reflection->onAttract = false;
	reflection->m_scl = { 1.0f,1.0f };
	reflection->m_speed = { 0.0f,0.0f };
	reflection->m_accel = { 0.0f,0.0f };
	reflection->m_attract = { 0.0f,0.0f };
	reflection->m_time = -1.0f;
	reflection->m_mode = -1;
	reflection->m_rad = 50.0f;
	reflection->m_rect = { 100.0f,100.0f };
	InitImage(&reflection->m_image, getTexture(textureLoaderNS::REFLECTION), reflection->m_pos.x, reflection->m_pos.y, 64.0f, 64.0f);
}