#include "BlackHole.h"
#include "input.h"
#include "action.h"
#include "Stage.h"

void initializeBlackHole(ObjStr* blackHole, ObjStr* others,int targetNum)
{
	blackHole->m_use = false;
	blackHole->onAttract = false;
	blackHole->m_scl = { 1.0f,1.0f };
	blackHole->m_speed = { 0.0f,0.0f };
	blackHole->m_accel = { 0.0f,0.0f };
	blackHole->m_attract = { 0.0f,0.0f };
	blackHole->m_time = -1.0f;
	blackHole->m_mode = -1;
	blackHole->m_rad = 50.0f;
	blackHole->m_rect = { 80.0f,80.0f };
	InitImage(&blackHole->m_image, getTexture(textureLoaderNS::BLACK_HOLE), blackHole->m_pos.x, blackHole->m_pos.y, 80.0f, 80.0f);
	//�u���b�N�z�[���̉e�����󂯂�I�u�W�F�N�g���Z�b�g����
	blackHole->m_tar = others;
	blackHole->targetNum = targetNum;
}

void setBlackHole(ObjStr* blackHole) {
	blackHole->m_use = !blackHole->m_use;

	if (blackHole->m_use)
		makeMagic_On(getEffect(), { (float)getMouseX(), (float)getMouseY() });//����0531 �}�E�X�̈ʒu�ɖ��@�w�z�u
	else
		makeMagic_Off(getEffect(), getObjectCenter(blackHole));//����0531 BH�������ʒu�ɖ��@�w�z�u

	blackHole->m_pos = D3DXVECTOR2{ (float)getMouseX(),(float)getMouseY() } - getObjectFar_PosToCenter(blackHole);
};

void updateBlackHole(ObjStr* blackHole) {
	if (getMouseLButtonTrigger()) // ���N���b�N�ŃZ�b�g
		setBlackHole(blackHole);
	if (blackHole->m_use == false)return;
	// ���͂��v�Z����
	for (int i = 0; i < blackHole->targetNum; i++)
		attractObject(&blackHole->m_tar[i], blackHole);

	for (ObjStr &i : *(getCometClass()->getDynObj()))
		attractObject(&i, blackHole);

};

void attractObject(ObjStr* object, ObjStr*blackHole) {
	if (!object->onAttract) return;//���͉e�����󂯂邩
	blackHole->m_attract = objectDirection(blackHole, object) * VALUE_ATTRACTION;
	if (objectLength(blackHole, object) <= RANGE_ATTRACTION)
	{// �I�u�W�F�N�g�̋��������͂̓����͈͓��Ȃ��
		// �I�u�W�F�N�g�̉����x�ֈ��͂����Z����
		object->m_accel =
			blackHole->m_attract * (1 - (objectLength(blackHole, object) / RANGE_ATTRACTION));
			// (����) * (1 - �I�u�W�F�N�g����/���͔͈�)
	}
}

void sendObject(ObjStr* collisionObject,ObjStr* blackHole)
{
	if (blackHole->whiteHole->m_use)
		collisionObject->m_pos = getObjectCenter(blackHole->whiteHole) - getObjectFar_PosToCenter(collisionObject);
	else
		actSplit(collisionObject,blackHole,getEffect());
}//����