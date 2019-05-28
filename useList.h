//����
#pragma once

#include "main.h"
#include "dataList.h"
#include "StageClass.h"

//�N����
void initializeObjList(DataList* typeCompat, DataList* xBased, DataList* result);
//�I����
void uninitializeObjList(DataList* typeCompat, DataList* xBased, DataList* result);
//�X�e�[�W�J�n���AxBased/result�Ƀ_�~�[�m�[�h��o�^�AxBased�ɃI�u�W�F�N�g�̒[��S�ēo�^
void startObjList(StageClass* stage, DataList* typeCompat, DataList* xBased, DataList* result);
//�X�e�[�W�I�����AxBased��result�𖕏�
void finishObjList(DataList* typeCompat, DataList* xBased, DataList* result);

//���t���[���AxBased���X�g�̏�Ԃ��ێ��Aresult���X�g���쐬�A�y��func(�悻��������������)�����s���Č��ʂ�bool���L�^
void updateObjList(DataList* typeCompat,DataList* xBased, DataList* result);
//���t���[���A���ɍ�������ʃ��X�g��S������鏈��(�s�s�����o�����Ȃ̂ŏo���Ƃ��͕ς��܂�)
	void checkResultList(DataList* result, void func(ObjStr* a, ObjStr* b));//�߂�l�Ȃ�
	//���ʃ��X�g����Afunc�̌��ʂ�false�ȃm�[�h���폜
	void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool
	//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�true�Ȃ��̂�true�ɏ���������
	void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool
	//���ʃ��X�g�̒��ŁAfunc�̌��ʂ�false�Ȃ��̂�false�ɏ���������
	void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//�߂�lbool



//���t���[���A���X�g�̒��g��S�ĕ`��
void printList(DataList* draw);
