//stage�V�[��
#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include "textureLoader.h"
#include "object.h"
#include "Select_Game.h" // ����ǉ�
#include "useList.h"//����0518
#include "collision.h"//����0518 �R���W�������̊֐������X�g�ɓn������
#include "effect.h"//����0525 �G�t�F�N�g
#include "StageClass.h"

StageClass stage;//�X�e�[�W�ʃf�[�^

Image gameBG;
DataList xBasedList;//����0518 x���W���E�I�u�W�F�N�g�E���X�g(initialize�ō���ăQ�[�����ʗp)
DataList resultList;//����0518 �m���ߌ��ʁE�I�u�W�F�N�g�֌W�E���X�g(update�Ŗ��t���[������Ďg���̂�)
DataList typeList_col;//����0525 �^�C�v�������X�g�A�Փ˗p(initialize�ō���ăQ�[�����ʗp)
EffList effectList;//����0525 �G�t�F�N�g�������������X�g(initialize�ō���ăQ�[�����ʗp)

void initializeStage() {
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};

void startStage() {
	
	//�X�e�[�W�Z���N�g�ŁA�X�e�[�W�ϐ����珉��������悤�ɂ���:�Ƃ肠�����X�e�[�W�P
	stage.initialize(stageNS::STAGE01);//����
	initializeEffect(&effectList);//����0525
	initializeObjList(&stage, &xBasedList, &resultList);


};//����0518 �V�����X�e�[�W�ɓ���O�ɌĂԊ֐�

void updateStage() {
	// ����ǉ�
	// timer��main�ɂ��邩��A������if�����邩�A������timer�������Ă��邩�ǂ��炪������
	// ���V����Timer�N���X�̃C���X�^���X���쐬����Ɨǂ��Ǝv���܂��B

	bool p_pause = *getPause();
	updatePause();
	// ��̂����܂�
	stage.update();//����
	if (getMouseLButtonTrigger() || getMouseRButtonTrigger())
		makeParticle(&effectList, { (float)getMouseX() + 40.0f, (float)getMouseY() + 40.0f });//����0525
	updateEffect(&effectList);//����0525

	updateObjList(&xBasedList, &resultList, checkHitObjRR);//����0518 x�����X�g���X�V�A�����i�s�I�ɃR���W�����֐���n���Ă��̌��ʃ��X�g���擾
//	cutResultList(&resultList, checkTypeComp_A);//����0525
};

void drawStage() {
	DrawImage(&gameBG);
	stage.draw();//����
	drawEffect(&effectList);//����0525
	drawPause(); // ���
};

void printStage() {
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "�}�E�X���{�^���������œ��̓_�C�A���O�{�b�N�X��\������", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());

	if (GetKeyboardPress(DIK_LCONTROL)/*��CTRL*/) printList(&xBasedList);//����0518 x�����X�g�̒��g�����o��
	if (GetKeyboardPress(DIK_M)/*�ECTRL*/) printList(&resultList);//����0518 ���ʃ��X�g�̒��g�����o��
	stage.print();//����
};

void unInitializeStage() {
	finishStage();//����0518
};

void finishStage() {
	stage.uninitialize();//����
	uninitializeEffect(&effectList);//����0525
	uninitializeObjList(&xBasedList, &resultList);
};//����0518 ���̃X�e�[�W����߂���ɌĂԊ֐�