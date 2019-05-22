//����
#pragma once

#include "main.h"
#include "dataList.h"

//�X�e�[�W�J�n���AxBased/result�Ƀ_�~�[�m�[�h��o�^�AxBased�ɃI�u�W�F�N�g�̒[��S�ēo�^
void initializeObjList(StageObj* p_stageobj, DataList* xBased, DataList* result);
//�X�e�[�W�I�����AxBased��result�𖕏�
void uninitializeObjList(DataList* xBased, DataList* result);

//���t���[���AxBased���X�g�̏�Ԃ��ێ��Aresult���X�g���쐬�A�y��process(�悻��������������)�����s���Č��ʂ�bool���L�^
void updateObjList(DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b));
//���t���[���A���ɍ�������ʃ��X�g��S������鏈��(�s�s�����o�����Ȃ̂ŏo���Ƃ��͕ς��܂�)
	void checkResultList(DataList* result, void process(ObjStr* a, ObjStr* b));//�߂�l�Ȃ�
	//���ʃ��X�g����Aprocess�̌��ʂ�false�ȃm�[�h���폜
	void check_cutResultList(DataList* result, bool process(ObjStr* a, ObjStr* b));//�߂�lbool
	//���ʃ��X�g�̒��ŁAprocess�̌��ʂ�true�Ȃ��̂�true�ɏ���������
	void check_updateOrResultList(DataList* result, bool process(ObjStr* a, ObjStr* b));//�߂�lbool
	//���ʃ��X�g�̒��ŁAprocess�̌��ʂ�false�Ȃ��̂�false�ɏ���������
	void check_updateAndResultList(DataList* result, bool process(ObjStr* a, ObjStr* b));//�߂�lbool



//���t���[���A���X�g�̒��g��S�ĕ`��
void printList(DataList* draw);
