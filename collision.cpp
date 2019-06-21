#include "collision.h"

//�I�u�W�F�N�g���m�̓����蔻��(�~*�~)
bool checkHitObjCC(ObjStr* p_obj1, ObjStr* p_obj2){
	//����A�I�u�W�F�N�g��m_pos�͍���̍��W�Ȃ̂ŁA�܂����S���o��
	D3DXVECTOR2 center1 = getObjectCenter(p_obj1);
	D3DXVECTOR2 center2 = getObjectCenter(p_obj2);

	if (((center1.x - center2.x)*(center1.x - center2.x)) + ((center1.y - center2.y)*(center1.y - center2.y))
		<= ((p_obj1->m_rad + p_obj2->m_rad) * (p_obj1->m_rad + p_obj2->m_rad))){
		return true;
	}

	return false;
};

//�I�u�W�F�N�g���m�̓����蔻��(��`*��`)
bool checkHitObjRR(ObjStr* p_obj1, ObjStr* p_obj2) {
	D3DXVECTOR2 rect1 = getObjectFar_PosToCorner(p_obj1);
	D3DXVECTOR2 rect2 = getObjectFar_PosToCorner(p_obj2);

	if (((p_obj1->m_pos.x > p_obj2->m_pos.x && p_obj1->m_pos.x < p_obj2->m_pos.x + rect2.x) ||
		(p_obj2->m_pos.x > p_obj1->m_pos.x && p_obj2->m_pos.x < p_obj1->m_pos.x + rect1.x)) &&
		((p_obj1->m_pos.y > p_obj2->m_pos.y && p_obj1->m_pos.y < p_obj2->m_pos.y + rect2.y) ||
		(p_obj2->m_pos.y > p_obj1->m_pos.y && p_obj2->m_pos.y < p_obj1->m_pos.y + rect1.y))){
		return true;
	}
	else{
		return false;
	}

};

//�I�u�W�F�N�g���m�̓����蔻��(�~*��`)
bool checkHitObjCR(ObjStr* p_obj1, ObjStr* p_obj2) {
	//����A�I�u�W�F�N�g��m_pos�͍���̍��W�Ȃ̂ŁA�܂����S���o��
	D3DXVECTOR2 center1 = getObjectCenter(p_obj1);

	//�~�̒��S�_�����`�̂P�ԋ߂�X���W
	D3DXVECTOR2 pos;
	if (center1.x < p_obj1->m_pos.x){
		pos.x = p_obj1->m_pos.x;
	}
	else if (center1.x > p_obj1->m_pos.x + p_obj1->m_rect.x) {
		pos.x = p_obj1->m_pos.x + p_obj1->m_rect.x;
	}
	else {
		pos.x = center1.x;
	}
	//�~�̒��S�_�����`�̂P�ԋ߂�Y���W
	if (center1.y < p_obj1->m_pos.y) {
		pos.y = p_obj1->m_pos.y;
	}
	else if (center1.y > p_obj1->m_pos.y + p_obj1->m_rect.y) {
		pos.y = p_obj1->m_pos.y + p_obj1->m_rect.y;
	}
	else {
		pos.x = center1.y;
	}

	//��������ɏՓ˔���
	float distance[2] = {fabsf(center1.x - pos.x),fabsf(center1.y - pos.y)};
	float dis = sqrtf((distance[0]* distance[0])+(distance[1]*distance[1]));
	if (dis < p_obj1->m_rad){
		return true;
	}
	return false;

};

// ��]���Ă����`�̒��_���v�Z
D3DXVECTOR2 computeRotatedBox(ObjStr* p_obj)
{
	// ����A�I�u�W�F�N�g��m_pos�͍���̍��W�Ȃ̂ŁA���S���o��
	D3DXVECTOR2 center = getObjectCenter(p_obj);
	D3DXVECTOR2 P_C = getObjectFar_PosToCenter(p_obj);

	// center�𒆐S�Ƃ������[�J�����W��p���āA��]��̍��W�����߂�
	p_obj->m_corner[0].x = (float)(center.x + (-P_C.x * cos(p_obj->m_rot) + P_C.y * sin(p_obj->m_rot)));
	p_obj->m_corner[0].y = (float)(center.y + (-P_C.x * sin(p_obj->m_rot) - P_C.y * cos(p_obj->m_rot)));

	p_obj->m_corner[1].x = (float)(center.x + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * cos(p_obj->m_rot) - (p_obj->m_pos.y - center.y) * sin(p_obj->m_rot)));
	p_obj->m_corner[1].y = (float)(center.y + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * sin(p_obj->m_rot) + (p_obj->m_pos.y - center.y) * cos(p_obj->m_rot)));

	p_obj->m_corner[2].x = (float)(center.x + (-P_C.x * cos(p_obj->m_rot) + P_C.y * sin(p_obj->m_rot)));
	p_obj->m_corner[2].y = (float)(center.y + (-P_C.x * sin(p_obj->m_rot) - P_C.y * cos(p_obj->m_rot)));

	p_obj->m_corner[3].x = (float)(center.x + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * cos(p_obj->m_rot) - (p_obj->m_pos.y + p_obj->m_rect.y - center.y) * sin(p_obj->m_rot)));
	p_obj->m_corner[3].y = (float)(center.y + ((p_obj->m_pos.x + p_obj->m_rect.x - center.x) * sin(p_obj->m_rot) + (p_obj->m_pos.y + p_obj->m_rect.y - center.y) * cos(p_obj->m_rot)));

	return center;
}

//computeRotateBox�����ɉ�]���Ă����̋�`�̓����蔻������
/**
bool checkHitRotateObjRR(ObjStr* p_obj1, ObjStr* p_obj2) {
	//2�̃I�u�W�F�N�g��m_corner���X�V����
	computeRotatedBox(p_obj1);
	computeRotatedBox(p_obj2);


}
**/