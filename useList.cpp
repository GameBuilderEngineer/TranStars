//����
#include "useList.h"
#include "collision.h"//����0527 �R���W�������̊֐������X�g�ɓn������
#include "effect.h"//����0527 �G�t�F�N�g
#include "BlackHole.h"//����0527 �G�t�F�N�g

void optimizeObjList_getResult(DataList* typeCompat, DataList* xBased, DataList* result);
void checkCheckList(DataList* checkList, DataList* typeCompat, DataList* result);
void startTypeCompatList(DataList* typeCompat);

void initializeObjList(DataList* typeCompat, DataList* xBased, DataList* result) {
	Initialize(xBased);
	Initialize(result);
	Initialize(typeCompat);
}
void uninitializeObjList(DataList* typeCompat,DataList* xBased, DataList* result) {
	Terminate(typeCompat);
	Terminate(xBased);
	Terminate(result);
}
void startObjList(StageClass* stage, DataList* typeCompat, DataList* xBased, DataList* result) {
	for (int i = 0; i < stage->getObjNum(); i++) {
		setObjEdge(xBased, &stage->getObj()[i]);
		//�I�u�W�F�N�g�S�Ă̍��[�E�E�[���ꂼ����m�[�h�Ƃ��ă��X�g�ɓo�^
	}
	startTypeCompatList(typeCompat);
}
void finishObjList(DataList* typeCompat, DataList* xBased, DataList* result) {
	Clear(typeCompat);
	Clear(xBased);
	Clear(result);
}

void updateObjList(DataList* typeCompat,DataList* xBased, DataList* result) {
	Clear(result);//���t���[���A�O��result��(�v��Ȃ��{�����܂łɏ����Ƃ��Ȃ��Ⴂ���Ȃ��̂�)����
	sortObjEdgeListByX(xBased);//x�[���X�g�ɃI�u�W�F�N�g�̈ړ��𔽉f
	optimizeObjList_getResult(typeCompat, xBased, result);
}

//���ɍ�������ʃ��X�g��S��func�ŎQ�Ƃ���
void checkResultList(DataList* result, void func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(result))
		func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}

//���ʃ��X�g����Afunc�̌��ʂ�false�ȃm�[�h���폜
void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(result))
		if (!func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR)) RemoveCurrent(result);
}
//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�true�Ȃ��̂�true�ɏ���������
void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(result))
		if (!result->crnt->d._oC.m_use) result->crnt->d._oC.m_use = func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}
//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�false�Ȃ��̂�false�ɏ���������
void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(result))
		if (result->crnt->d._oC.m_use) result->crnt->d._oC.m_use = func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}

//�I�u�W�F�N�g�̒[��x�����X�g�ɓo�^
void setObjEdge(DataList* xBased, ObjStr* p_obj) {
	float size = getObjectSizeLonger(p_obj);//���a�ƕӁA�ǂ��炪�����蔻�肩�͂Ƃ�����������
	InsertRearEdges(xBased, p_obj, p_obj->m_image.width / 2.0f - size, p_obj->m_image.width / 2.0f + size);
}

//���X�g�̒��g����ʂɕ\��
void printList(DataList* draw) {
	Print(draw);
}

//���t���[���AxBased��func(�Ȃ�炩�̏���)�����Ƃ�result���쐬
void optimizeObjList_getResult(DataList* typeCompat, DataList* xBased, DataList* result) {

	//compat�Ƃ́H�c�^�C�v�֌W�B�]�T����������^�C�v�֌W�ɂ���������������

	DataList checkList; Initialize(&checkList);// �`�F�b�N���X�g(xBased������Ԃ����K�v�ȃ��X�g)�쐬

	xBased->crnt = xBased->head;// x�����X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(xBased)) {
		if (!xBased->crnt->d._oE.mp_obj->m_use) continue;//use��false�Ȃ�l���Ȃ�

		if (xBased->crnt->d._oE.mp_L == NULL) {// ���ׂ��I�u�W�F�N�g�[���I�u�W�F�N�g�̍��[������
			InsertRear(&checkList, xBased->crnt->d);//���̃I�u�W�F�N�g���`�F�b�N���X�g�ɓo�^(�E�[�͓o�^���Ȃ�)

			//�`�F�b�N���X�g�ɐV�����I�u�W�F�N�g�[���ǉ�����Ă��Ȃ��Ȃ��
			//���U���g���X�g�ɐV�������̂��������͂Ȃ��̂Œ��ג����K�v�͂Ȃ�

			checkCheckList(&checkList, typeCompat, result);//�`�F�b�N���X�g���`�F�b�N
		}
		if (xBased->crnt->d._oE.mp_L != NULL) {// ���ׂ��I�u�W�F�N�g�[���I�u�W�F�N�g�̉E�[������
			checkList.crnt = SearchObjEdge(&checkList, xBased->crnt->d._oE.mp_L->mp_obj);
			RemoveCurrent(&checkList);
			// �E�[�܂ŗ����̂ŁA�Ή����鍶�[�m�[�h���`�F�b�N���X�g����T���ď���
			// NULL�ł��邱�Ƃ͂Ȃ���
		}
	}

	Terminate(&checkList);//�`�F�b�N���X�g�o��
}

//�`�F�b�N���X�g�ƃ^�C�v�������X�g�����A�^�C�v�������X�g�ɓo�^���ꂽ�֐��̌��ʂ����U���g���X�g�ɋL�^
void checkCheckList(DataList* checkList, DataList* typeCompat, DataList* result) {
	DataNode *sub_crnt; checkList->crnt = checkList->head;
	while (Next(checkList)) {//���X�g���_�~�[�݂̂������茩�I�������E�o
		sub_crnt = checkList->crnt;
		while (Next(checkList)) {
			//�J�����g�ȑO�̃m�[�h�͈�傫�����[�v�Œ��׏I����Ă��锤�Ȃ̂Ŕ�ׂ�̂�crnt�̎�����ł悢
			if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj) == NULL) {// �܂����ʃ��X�g�ɂȂ����̂�������
				typeCompat->crnt = typeCompat->head;//�^�C�v�\�̃J�����g�����Z�b�g
				while (SearchNextTypeCompat(typeCompat, sub_crnt->d._oE.mp_obj->m_type, checkList->crnt->d._oE.mp_obj->m_type)
					!= NULL) {//����J�����g����o�����A����������J�����g�𓮂��������B�w�b�_�ɒH�蒅������NULL
					InsertRearCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj, 
						(*typeCompat->crnt->d._tC.mp_func)(sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj));
						// �`�F�b�N���X�g�ɓo�^����Ă����֐�(*mp_func)�œ�������(bool)��o�^
				}
			}
		}
		checkList->crnt = sub_crnt;//�傫��while�̃J�����g�܂Ŗ߂�
	}
}


void startTypeCompatList(DataList* typeCompat) {
	setTypeCompats(typeCompat, NO_TYPE, TYPE_MAX, NO_TYPE, TYPE_MAX, true, &checkHitObjRR);//�S�^�C�v

	deleteTypeCompats(typeCompat, CHARA_BLACKHOLE, CHARA_BLACKHOLE, NO_TYPE, TYPE_MAX, true, &checkHitObjRR);//�u���b�N�z�[���ƑS�^�C�v

	deleteTypeCompats(typeCompat, NO_TYPE, TYPE_MAX, CHARA_BLACKHOLE, CHARA_BLACKHOLE, true, &checkHitObjRR);//�S�^�C�v�ƃu���b�N�z�[��
	setTypeCompats(typeCompat, NO_TYPE, TYPE_MAX, CHARA_BLACKHOLE, CHARA_BLACKHOLE, true, &sendObject);//�S�^�C�v�ƃu���b�N�z�[��
}

