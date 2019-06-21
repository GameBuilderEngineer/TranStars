//����
#pragma once

#include "main.h"
#include "dataList.h"
#include "funcTypeList.h"
#include "StageClass.h"

//�N����
void initializeObjList(DataList* data);
void initializeTypeFuncList(TF_List* typeFunc);

void setCollisionList(TF_List* typeFunc, objTypes type1, objTypes type2, bool(*p_func)(ObjStr* a, ObjStr* b));
void setCollisionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	bool(*p_func)(ObjStr* a, ObjStr* b));
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b));
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b));
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff));
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff));

void optimizeActionList(TF_List* typeFunc);
//�I����
void uninitializeObjList(DataList* data);
void uninitializeTypeFuncList(TF_List* typeFunc);

//�X�e�[�W�J�n���AxBased�ɃI�u�W�F�N�g�̒[��S�ēo�^
//void startObjList(StageClass* stage, DataList* xBased, DataList* result);
//�X�e�[�W�I�����AxBased��result�̒��g�����
void finishObjList(DataList* data);

//���t���[���A���X�g�̒��g��S�ĕ`��
void printList(DataList* draw);

//���t���[�����߁AxBased���ێ����AtypeFunc������func(�R���W��������)�����Ƃ�result���쐬
void makeResultList(TF_List* col, DataList* xBased, DataList* result);
//�O�̃t���[���̃R���W�������ʂ�����
void clearResultList(DataList* result);

//���t���[���A���ʃ��X�g(�̃I�u�W�F�N�g�Q��)���A�^�C�v���X�g(�̊֐�)�ɒʂ�����
void checkResultList(TF_List* typeFunc, DataList* result, EffList* eff);

/*
//���ʃ��X�g����Afunc�̌��ʂ�false�ȃm�[�h���폜
void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool
//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�true�Ȃ��̂�true�ɏ���������
void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool
//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�false�Ȃ��̂�false�ɏ���������
void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool
*/

//�I�u�W�F�N�g�̒[��x�����X�g�ɓo�^
void setObjEdge(DataList* xBased, ObjStr* p_obj);
