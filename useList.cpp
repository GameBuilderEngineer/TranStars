//����
#include "useList.h"

void checkCheckList(DataList* checkList, TF_List* col, DataList* result);
void checkCollision_updateResult(TF_List* col, DataList* result, ObjStr* x, ObjStr* y);

void checkTypeFunc(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff);
void checkTypeFuncEach(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff);

//��������

void initializeObjList(DataList* data) {
	Initialize(data);
}
void initializeTypeFuncList(TF_List* typeFunc) {
	Initialize(typeFunc);
}

//�^�C�v�t�@���N���X�g��ݒ�
void setCollisionList(TF_List* typeFunc, objTypes type1, objTypes type2, bool(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFunc(typeFunc, type1, type2, true,FUNC_COLLISION, castFunc(p_func));
}
void setCollisionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	bool(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFuncs(typeFunc, type1L, type1H, type2L, type2H, true, FUNC_COLLISION, castFunc(p_func));
}
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFunc(typeFunc, type1, type2, true, FUNC_ACTION, castFunc(p_func));
}
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFuncs(typeFunc, type1L, type1H, type2L, type2H, true, FUNC_ACTION, castFunc(p_func));
}
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff)) {
	setTypeFunc(typeFunc, type1, type2, true, FUNC_ACTION_EFFECT, castFunc(p_func));
}
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff)) {
	setTypeFuncs(typeFunc, type1L, type1H, type2L, type2H, true, FUNC_ACTION_EFFECT, castFunc(p_func));
}
void optimizeActionList(TF_List* typeFunc) {
	optimizeTypeFuncs(typeFunc);//type1,2�ɁA�g�ݍ��킹�ꏏ�ŏ������t�A�����֐����o�^����Ă��܂��̂������
}

//��������

void uninitializeObjList(DataList* data) {
	Terminate(data);
}
void uninitializeTypeFuncList(TF_List* typeFunc) {
	Terminate(typeFunc);
}

//void startObjList(StageClass* stage, DataList* xBased, DataList* result) {
//	for (int i = 0; i < stage->getObjNum(); i++)
//		setObjEdge(xBased, &stage->getObj()[i]);
//		//�I�u�W�F�N�g�S�Ă̍��[�E�E�[���ꂼ����m�[�h�Ƃ��ă��X�g�ɓo�^
//}

void finishObjList(DataList* data) {
	Clear(data);
}

//���t���[�����߁AxBased���ێ����AtypeFunc������func(�R���W��������)�����Ƃ�result���쐬
void makeResultList(TF_List* col, DataList* xBased, DataList* result) {
	sortObjEdgeListByX(xBased);//x�[���X�g�ɃI�u�W�F�N�g�̈ړ��𔽉f

	DataList checkList; Initialize(&checkList);// �`�F�b�N���X�g(xBased������Ԃ����K�v�ȃ��X�g)�쐬

	xBased->crnt = xBased->head;// x�����X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(xBased)) {
		if (!xBased->crnt->d._oE.mp_obj->m_use) continue;//use��false�Ȃ�l���Ȃ�

		if (xBased->crnt->d._oE.mp_L == NULL) {// ���ׂ��I�u�W�F�N�g�[���I�u�W�F�N�g�̍��[������
			InsertRear(&checkList, xBased->crnt->d);//���̃I�u�W�F�N�g���`�F�b�N���X�g�ɓo�^(�E�[�͓o�^���Ȃ�)

			//�`�F�b�N���X�g�ɐV�����I�u�W�F�N�g�[���ǉ�����Ă��Ȃ��Ȃ��
			//���U���g���X�g�ɐV�������̂��������͂Ȃ��̂Œ��ג����K�v�͂Ȃ�

			checkCheckList(&checkList, col, result);//�`�F�b�N���X�g���`�F�b�N
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
void checkResultList(TF_List* typeFunc, DataList* result, EffList* eff){
	result->crnt = result->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(result))
		if (result->crnt->d._oC.m_use == true)
			checkTypeFuncEach(typeFunc, result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR, eff);
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
	float size = getObjectHarfSizeLonger(p_obj);//���a�ƕӁA�ǂ��炪�����蔻�肩�͂Ƃ�����������
	InsertRearEdges(xBased, p_obj, getObjectFar_PosToCenter(p_obj).x - size, getObjectFar_PosToCenter(p_obj).x + size);
}

//���X�g�̒��g����ʂɕ\��
void printList(DataList* draw) {
	Print(draw);
}


//////////////////���[�J��

//�`�F�b�N���X�g�ƃ^�C�v�������X�g�����A�^�C�v�������X�g�ɓo�^���ꂽ�֐��̌��ʂ����ʃ��X�g�ɋL�^
void checkCheckList(DataList* checkList, TF_List* col, DataList* result) {
	DataNode *sub_crnt; checkList->crnt = checkList->head;
	while (Next(checkList)) {//���X�g���_�~�[�݂̂������茩�I�������E�o
		sub_crnt = checkList->crnt;
		while (Next(checkList))
			//�J�����g�ȑO�̃m�[�h�͈�傫�����[�v�Œ��׏I����Ă��锤�Ȃ̂Ŕ�ׂ�̂�crnt�̎�����ł悢
			if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj) == NULL)// �܂����ʃ��X�g�ɂȂ����̂�������
				checkCollision_updateResult(col, result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj);

		checkList->crnt = sub_crnt;//�傫��while�̃J�����g�܂Ŗ߂�
	}
}

//�Q�̃I�u�W�F�N�g���^�C�v���X�g(�ɓo�^���ꂽ�֐�)�ɒʂ��A���ʂ����ʃ��X�g�ɋL�^
void checkCollision_updateResult(TF_List* col, DataList* result, ObjStr* x, ObjStr* y) {
	col->crnt = col->head;//�^�C�v�\�̃J�����g�����Z�b�g
	while (SearchNextTF_byObjType(col, x->m_type, y->m_type)
		!= NULL)//����J�����g����o�����A����������J�����g�𓮂��������B�w�b�_�ɒH�蒅������NULL

			InsertRearCon(result, x, y, (*col->crnt->d.mp_func._b)(x, y));
				// ���ʃ��X�g�ɃI�u�W�F�N�g�̑g�ݍ��킹�ƁA������^�C�v���X�g(�̊֐�)�ɒʂ��ē���bool���ʂ�o�^
}

//�Q�̃I�u�W�F�N�g���^�C�v�������X�g�ɓo�^���ꂽ�֐��S�Ăɒʂ�(�L�^�Ȃ�)
void checkTypeFunc(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff) {
	typeFunc->crnt = typeFunc->head;//�^�C�v�\�̃J�����g�����Z�b�g
	while (SearchNextTF_byObjType(typeFunc, x->m_type, y->m_type)
		!= NULL)//����J�����g����o�����A����������J�����g�𓮂��������B�w�b�_�ɒH�蒅������NULL
		if (typeFunc->crnt->d.fType != FUNC_ACTION_EFFECT) (*typeFunc->crnt->d.mp_func._v)(x, y);
		else (*typeFunc->crnt->d.mp_func._ef)(x, y, eff);
}

//x,y�����s����
void checkTypeFuncEach(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff) {
	checkTypeFunc(typeFunc, x, y, eff);

	if (x->m_type != y->m_type)//�^�C�v�������łȂ���΋t�ɂ��Ă������m���߂�
		checkTypeFunc(typeFunc, y, x, eff);
}