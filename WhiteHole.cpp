#include "WhiteHole.h"
#include "input.h"

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
	if (getMouseRButtonTrigger()) // �E�N���b�N�ŃZ�b�g
		setWhiteHole(whiteHole);
};


void  setWhiteHole(ObjStr* whiteHole) {
	whiteHole->m_use = !whiteHole->m_use;
	whiteHole->m_pos = D3DXVECTOR2{ (float)getMouseX(),(float)getMouseY() };
};