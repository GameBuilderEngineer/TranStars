//����
#include "useList.h"

void checkCheckList(DataList* checkList, DataList* typeFunc, DataList* result);
void checkTypeFunc_updateResult(DataList* typeFunc, DataList* result, ObjStr* x, ObjStr* y);
void checkTypeFunc(DataList* typeFunc, ObjStr* x, ObjStr* y);
void checkTypeFuncEach(DataList* typeFunc, ObjStr* x, ObjStr* y);

void initializeObjList(DataList* xBased, DataList* result) {
	Initialize(xBased);
	Initialize(result);
}
void initializeTypeFuncList(DataList* typeFunc) {
	Initialize(typeFunc);
}
void setTypeFuncList(DataList* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H
	, bool(*p_func)(ObjStr* a, ObjStr* b)
	, bool optimizeUse) {
	setTypeFuncs(typeFunc, type1L, type1H, type2L, type2H, true, p_func);
	if (optimizeUse)
		optimizeTypeFuncs(typeFunc);//type1,2�ɁA�g�ݍ��킹�ꏏ�ŏ������t�A�����֐����o�^����Ă��܂��̂������
}

void uninitializeObjList(DataList* xBased, DataList* result) {
	Terminate(xBased);
	Terminate(result);
}
void uninitializeTypeFuncList(DataList* typeFunc) {
	Terminate(typeFunc);
}

void startObjList(StageClass* stage, DataList* xBased, DataList* result) {
	for (int i = 0; i < stage->getObjNum(); i++)
		setObjEdge(xBased, &stage->getObj()[i]);
		//�I�u�W�F�N�g�S�Ă̍��[�E�E�[���ꂼ����m�[�h�Ƃ��ă��X�g�ɓo�^
}

void finishObjList(DataList* xBased, DataList* result) {
	Clear(xBased);
	Clear(result);
}

//���t���[���AxBased���ێ����AtypeFunc������func�����Ƃ�result���쐬
void makeResultList(DataList* typeFunc, DataList* xBased, DataList* result) {
	sortObjEdgeListByX(xBased);//x�[���X�g�ɃI�u�W�F�N�g�̈ړ��𔽉f

	DataList checkList; Initialize(&checkList);// �`�F�b�N���X�g(xBased������Ԃ����K�v�ȃ��X�g)�쐬

	xBased->crnt = xBased->head;// x�����X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(xBased)) {
		if (!xBased->crnt->d._oE.mp_obj->m_use) continue;//use��false�Ȃ�l���Ȃ�

		if (xBased->crnt->d._oE.mp_L == NULL) {// ���ׂ��I�u�W�F�N�g�[���I�u�W�F�N�g�̍��[������
			InsertRear(&checkList, xBased->crnt->d);//���̃I�u�W�F�N�g���`�F�b�N���X�g�ɓo�^(�E�[�͓o�^���Ȃ�)

			//�`�F�b�N���X�g�ɐV�����I�u�W�F�N�g�[���ǉ�����Ă��Ȃ��Ȃ��
			//���U���g���X�g�ɐV�������̂��������͂Ȃ��̂Œ��ג����K�v�͂Ȃ�

			checkCheckList(&checkList, typeFunc, result);//�`�F�b�N���X�g���`�F�b�N
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

void clearResultList(DataList* result) {
	Clear(result);//���t���[���A�O��result��(�v��Ȃ��{�����܂łɏ����Ƃ��Ȃ��Ⴂ���Ȃ��̂�)����
}

//���ɍ�������ʃ��X�g���AtypeFuncList�̊֐��ɒʂ�
void checkResultList(DataList* typeFunc, DataList* result){
	result->crnt = result->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(result))
		if (result->crnt->d._oC.m_use == true)
			checkTypeFuncEach(typeFunc, result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}

/*
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
}*/

//�I�u�W�F�N�g�̒[��x�����X�g�ɓo�^
void setObjEdge(DataList* xBased, ObjStr* p_obj) {
	float size = getObjectSizeLonger(p_obj);//���a�ƕӁA�ǂ��炪�����蔻�肩�͂Ƃ�����������
	InsertRearEdges(xBased, p_obj, p_obj->m_image.width / 2.0f - size, p_obj->m_image.width / 2.0f + size);
}

//���X�g�̒��g����ʂɕ\��
void printList(DataList* draw) {
	Print(draw);
}


//////////////////���[�J��

//�`�F�b�N���X�g�ƃ^�C�v�������X�g�����A�^�C�v�������X�g�ɓo�^���ꂽ�֐��̌��ʂ����ʃ��X�g�ɋL�^
void checkCheckList(DataList* checkList, DataList* typeFunc, DataList* result) {
	DataNode *sub_crnt; checkList->crnt = checkList->head;
	while (Next(checkList)) {//���X�g���_�~�[�݂̂������茩�I�������E�o
		sub_crnt = checkList->crnt;
		while (Next(checkList))
			//�J�����g�ȑO�̃m�[�h�͈�傫�����[�v�Œ��׏I����Ă��锤�Ȃ̂Ŕ�ׂ�̂�crnt�̎�����ł悢
			if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj) == NULL)// �܂����ʃ��X�g�ɂȂ����̂�������
				checkTypeFunc_updateResult(typeFunc, result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj);

		checkList->crnt = sub_crnt;//�傫��while�̃J�����g�܂Ŗ߂�
	}
}

//�Q�̃I�u�W�F�N�g���^�C�v���X�g(�ɓo�^���ꂽ�֐�)�ɒʂ��A���ʂ����ʃ��X�g�ɋL�^
void checkTypeFunc_updateResult(DataList* typeFunc, DataList* result, ObjStr* x, ObjStr* y) {
	typeFunc->crnt = typeFunc->head;//�^�C�v�\�̃J�����g�����Z�b�g
	while (SearchNextTypeFunc(typeFunc, x->m_type, y->m_type)
		!= NULL)//����J�����g����o�����A����������J�����g�𓮂��������B�w�b�_�ɒH�蒅������NULL

			InsertRearCon(result, x, y, (*typeFunc->crnt->d._tF.mp_func)(x, y));
				// ���ʃ��X�g�ɃI�u�W�F�N�g�̑g�ݍ��킹�ƁA������^�C�v���X�g(�̊֐�)�ɒʂ��ē������ʂ�o�^
}

//�Q�̃I�u�W�F�N�g���^�C�v�������X�g�ɓo�^���ꂽ�֐��S�Ăɒʂ�(�L�^�Ȃ�)
void checkTypeFunc(DataList* typeFunc, ObjStr* x, ObjStr* y) {
	typeFunc->crnt = typeFunc->head;//�^�C�v�\�̃J�����g�����Z�b�g
	while (SearchNextTypeFunc(typeFunc, x->m_type, y->m_type)
		!= NULL)//����J�����g����o�����A����������J�����g�𓮂��������B�w�b�_�ɒH�蒅������NULL
		(*typeFunc->crnt->d._tF.mp_func)(x, y);
}

//x,y���������Ă������
void checkTypeFuncEach(DataList* typeFunc, ObjStr* x, ObjStr* y) {
	checkTypeFunc(typeFunc, x, y);

	if (x->m_type != y->m_type)//�����m���߂�
		checkTypeFunc(typeFunc, y, x);
}