#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include"textureLoader.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"
#include "Select_Game.h" // ����ǉ�
#include "useList.h"//����0518
#include "collision.h"//����0518 �R���W�������̊֐������X�g�ɓn������

MessageDialog mDialog;
InputDialog inDialog;

StageObj stageObj;//���� 0.02
Image gameBG;
DataList xBasedList;//����0518 x���W���E�I�u�W�F�N�g�E���X�g(�Q�[�����ʗp)
DataList resultList;//����0518 �m���ߌ��ʁE�I�u�W�F�N�g�֌W�E���X�g(���t���[���g���̂�)

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};
void startStage() {
	initializeObject(&stageObj, 0);//���� 0.02 �ЂƂ܂�0�X�e�[�W��
	initializeObjList(&stageObj, &xBasedList, &resultList);
};//����0518 �V�����X�e�[�W�ɓ���O�ɌĂԊ֐�
void updateStage() {
	// ����ǉ�
	// timer��main�ɂ��邩��A������if�����邩�A������timer�������Ă��邩�ǂ��炪������
	bool p_pause = *getPause();
	updatePause();
	// ��̂����܂�
	inDialog.update();
	mDialog.update();
	updateObject(&stageObj);
	updateObjList(&xBasedList, &resultList, checkHitObjRR);//����0518 x�����X�g���X�V�A�����i�s�I�ɃR���W�����֐���n���Ă��̌��ʃ��X�g���擾
	check_updateAndResultList(&resultList, checkHitObjCC);//����0518
	if (getMouseMButton())
	{
		inDialog.print("please InputText");
	}

};
void drawStage() {
	DrawImage(&gameBG);
	inDialog.draw();
	//mDialog.draw();
	drawObject(&stageObj);
	drawPause(); // ���

};

void printStage() {
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "�}�E�X���{�^���������œ��̓_�C�A���O�{�b�N�X��\������", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());

	if (GetKeyboardPress(DIK_LCONTROL)/*��CTRL*/) printList(&xBasedList);//����0518 x�����X�g�̒��g�����o��
	if (GetKeyboardPress(DIK_RCONTROL)/*�ECTRL*/) printList(&resultList);//����0518 ���ʃ��X�g�̒��g�����o��
	printObject(&stageObj);//���� 0.22
};
void unInitializeStage() {
	finishStage();//����0518
};
void finishStage() {
	uninitializeObject(&stageObj);
	uninitializeObjList(&xBasedList, &resultList);
};//����0518 ���̃X�e�[�W����߂���ɌĂԊ֐�
