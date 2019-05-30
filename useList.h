//����
#pragma once

#include "main.h"
#include "dataList.h"
#include "StageClass.h"

//�N����
void initializeObjList(DataList* xBased, DataList* result);
void initializeTypeCompatList(DataList* typeCompat, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H
	, bool(*p_func)(ObjStr* a, ObjStr* b)
	, bool optimizeUse);
	//�I����
void uninitializeObjList(DataList* xBased, DataList* result);
void uninitializeTypeCompatList(DataList* typeCompat);
//�X�e�[�W�J�n���AxBased/result�Ƀ_�~�[�m�[�h��o�^�AxBased�ɃI�u�W�F�N�g�̒[��S�ēo�^
void startObjList(StageClass* stage, DataList* xBased, DataList* result);

//�X�e�[�W�I�����AxBased��result�𖕏�
void finishObjList(DataList* xBased, DataList* result);

//���t���[���A���X�g�̒��g��S�ĕ`��
void printList(DataList* draw);

//���t���[���AxBased���X�g�̏�Ԃ��ێ��Aresult���X�g���폜���č쐬�A�y��typeCompat���o���Ă���֐������s���Č��ʂ�bool���L�^
void makeResultList(DataList* typeCompat, DataList* xBased, DataList* result);

void clearResultList(DataList* result);

//���t���[���A���ʃ��X�g(�̃I�u�W�F�N�g�Q��)���A�^�C�v���X�g(�̊֐�)�ɒʂ�����
	void checkResultList(DataList* typeCompat,DataList* result);

/*	//���ʃ��X�g����Afunc�̌��ʂ�false�ȃm�[�h���폜
	void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool
	//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�true�Ȃ��̂�true�ɏ���������
	void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool
	//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�false�Ȃ��̂�false�ɏ���������
	void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool*/

//�I�u�W�F�N�g�̒[��x�����X�g�ɓo�^
void setObjEdge(DataList* xBased, ObjStr* p_obj);
