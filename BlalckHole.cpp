#include "BlackHole.h"
#include "input.h"


void initializeBlackHole(ObjStr* blackHole, ObjStr* others,int targetNum)
{
	blackHole->m_use = false;
	blackHole->onAttract = false;
	blackHole->m_scl = { 1.0f,1.0f };
	blackHole->m_speed = { 0.0f,0.0f };
	blackHole->m_accel = { 0.0f,0.0f };
	blackHole->m_attract = { 0.0f,0.0f };
	blackHole->m_time = -1;
	blackHole->m_mode = -1;
	blackHole->m_rad = 50.0f;
	blackHole->m_rect = { 100.0f,100.0f };
	InitImage(&blackHole->m_image, getTexture(textureLoaderNS::BLACK_HOLE), blackHole->m_pos.x, blackHole->m_pos.y, 80.0f, 80.0f);
	//�u���b�N�z�[���̉e�����󂯂�I�u�W�F�N�g���Z�b�g����
	blackHole->m_tar = others;
	blackHole->targetNum = targetNum;
}

void setBlackHole(ObjStr* obj) {
	obj->m_use = !obj->m_use;
	obj->m_pos = D3DXVECTOR2{ (float)getMouseX(),(float)getMouseY() };
};

void updateBlackHole(ObjStr* blackHole) {
	if (getMouseLButtonTrigger()) // ���N���b�N�ŃZ�b�g
		setBlackHole(blackHole);
	if (blackHole->m_use == false)return;
	// ���͂��v�Z����
	for (int i = 0; i < blackHole->targetNum; i++) {
		if (!blackHole->m_tar[i].onAttract)continue;//���͉e�����󂯂邩
		blackHole->m_attract = objectDirection(blackHole, &blackHole->m_tar[i]) * VALUE_ATTRACTION;
		if (objectLength(blackHole, &blackHole->m_tar[i]) <= RANGE_ATTRACTION) 
		{// �I�u�W�F�N�g�̋��������͂̓����͈͓��Ȃ��
			// �I�u�W�F�N�g�̉����x�ֈ��͂����Z����
			blackHole->m_tar[i].m_accel =
				blackHole->m_attract * (1 - (objectLength(blackHole, &blackHole->m_tar[i]) / RANGE_ATTRACTION));
				// (����) * (1 - �I�u�W�F�N�g����/���͔͈�)
		}
	}
};

bool sendObject(ObjStr* collisionObject,ObjStr* blackHole)
{
	collisionObject->m_pos = blackHole->whiteHole->m_pos;
	return true;
}