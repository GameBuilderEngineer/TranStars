#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include"textureLoader.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"
#include "Select_Game.h" // ����ǉ�

MessageDialog mDialog;
InputDialog inDialog;

StageObj stageObj;//���� 0.02
Image gameBG;
void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	initializeObject(&stageObj,0);//���� 0.02 �ЂƂ܂�0�X�e�[�W��
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};
void updateStage() {
	// ����ǉ�
	// timer��main�ɂ��邩��A������if�����邩�A������timer�������Ă��邩�ǂ��炪������
	bool p_pause = *getPause();
	updatePause();
	// ��̂����܂�
	inDialog.update();
	mDialog.update();
	updateObject(&stageObj);
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

	printObject(&stageObj);//���� 0.22
};
void unInitializeStage() {
	uninitializeObject(&stageObj);
};