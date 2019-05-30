#include "Reflection.h"

void initializeReflection(ObjStr* reflection)
{
	reflection->m_scl = { 1.0f,1.0f };
	reflection->m_speed = { 0.0f,0.0f };
	reflection->m_accel = { 0.0f,0.0f };
	reflection->m_attract = { 0.0f,0.0f };
	reflection->m_time = -1;
	reflection->m_mode = -1;
	reflection->m_rad = 50.0f;
	reflection->m_rect = { 100.0f,100.0f };
	reflection->m_image.g_pD3DTexture = *getTexture(textureLoaderNS::BACK_GROUND);
	reflection->m_image.width = 100.0f;
	reflection->m_image.height = 100.0f;
	reflection->m_image.playAnime = false;
	reflection->m_image.ANIME_TIME = 1;
	reflection->m_image.ANIME_PATTERN = 1;
	reflection->m_image.DIVIDE_U = 1;
	reflection->m_image.DIVIDE_V = 1;
	InitImage(&reflection->m_image, getTexture(textureLoaderNS::MAGIC_CIRCLE), reflection->m_pos.x, reflection->m_pos.y, 160.0f, 160.0f);
}