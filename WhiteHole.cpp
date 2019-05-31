#include "WhiteHole.h"
#include "input.h"
#include "effect.h"
#include "stage.h"

void initializeWhiteHole(ObjStr* whiteHole)
{
	whiteHole->m_use = true;
	whiteHole->onAttract = false;
	whiteHole->m_scl = { 1.0f,1.0f };
	whiteHole->m_speed = { 0.0f,0.0f };
	whiteHole->m_accel = { 0.0f,0.0f };
	whiteHole->m_attract = { 0.0f,0.0f };
	whiteHole->m_time = -1;
	whiteHole->m_mode = -1;
	whiteHole->m_rad = 50.0f;
	whiteHole->m_rect = { 100.0f,100.0f };
	InitImage(&whiteHole->m_image, getTexture(textureLoaderNS::WHITE_HOLE), whiteHole->m_pos.x, whiteHole->m_pos.y, 80.0f, 80.0f);

}


void updateWhiteHole(ObjStr* whiteHole) {
	if (getMouseRButtonTrigger()) // 右クリックでセット
		setWhiteHole(whiteHole);
};


void  setWhiteHole(ObjStr* whiteHole) {
	whiteHole->m_use = !whiteHole->m_use;

	if (whiteHole->m_use)
		makeMagic(getEffect(), { (float)getMouseX(), (float)getMouseY() });//西川0531 マウスの位置に魔法陣配置
	else
		makeMagic(getEffect(), whiteHole->m_pos);//西川0531 BHがいた位置に魔法陣配置


	whiteHole->m_pos = D3DXVECTOR2{ 
		(float)getMouseX() - whiteHole->m_image.width / 2.0f,(float)getMouseY() - whiteHole->m_image.height / 2.0f };
};