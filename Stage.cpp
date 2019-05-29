//stage�V�[��
#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include "textureLoader.h"
#include "object.h"
#include "Select_Game.h" // ����ǉ�
#include "useList.h"//����0518
//#include "collision.h"//����0518 �R���W�������̊֐������X�g�ɓn������
#include "effect.h"//����0525 �G�t�F�N�g
#include "StageClass.h"

StageClass stage;//�X�e�[�W�ʃf�[�^

Image gameBG;
DataList typeCompatList;//����0527 �^�C�v�֌W�Ǝ��s����֐��̃��X�g
DataList xBasedList;//����0518 x���W���E�I�u�W�F�N�g�E���X�g(initialize�ō���ăQ�[�����ʗp)
DataList resultList;//����0518 �m���ߌ��ʁE�I�u�W�F�N�g�֌W�E���X�g(update�Ŗ��t���[������Ďg���̂�)
EffList effectList;//����0525 �G�t�F�N�g�������������X�g(initialize�ō���ăQ�[�����ʗp)

void initializeStage() {
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
	initializeObjList(&typeCompatList, &xBasedList, &resultList);//����0527
	initializeEffect(&effectList);//����0527
};

void startStage() {	
	//�X�e�[�W�Z���N�g�ŁA�X�e�[�W�ϐ����珉��������悤�ɂ���:�Ƃ肠�����X�e�[�W�P
	stage.initialize(stageNS::STAGE01);//����
	startEffect(&effectList);//����0527
	startObjList(&stage, &typeCompatList, &xBasedList, &resultList);//����0527

};//����0518 �V�����X�e�[�W�ɓ���O�ɌĂԊ֐�

void updateStage() {
	// ����ǉ�
	// timer��main�ɂ��邩��A������if�����邩�A������timer�������Ă��邩�ǂ��炪������
	// ���V����Timer�N���X�̃C���X�^���X���쐬����Ɨǂ��Ǝv���܂��B

	bool p_pause = *getPause();
	updatePause();
	// ��̂����܂�
	stage.update();//����
	if (getMouseLButtonTrigger())
		makeParticle(&effectList, { (float)getMouseX(), (float)getMouseY() });//����0525
	if (getMouseRButtonTrigger())
//		makeMagic(&effectList, { (float)getMouseX(), (float)getMouseY() });//����0526
		makeSplit(&effectList, { (float)getMouseX(), (float)getMouseY() }, &stage.getObj()[0].m_image);//����0527
	makeTail(&effectList, { stage.getObj()[0].m_pos.x + stage.getObj()[0].m_image.width / 2.0f,
		stage.getObj()[0].m_pos.y + stage.getObj()[0].m_image.height / 2.0f }, stage.getObj()[0].m_speed);//����0528
	updateEffect(&effectList);//����0525

	updateObjList(&typeCompatList, &xBasedList, &resultList);//����0527 x�����X�g���X�V�A�����i�s�I�ɃR���W�����֐���n���Ă��̌��ʃ��X�g���擾
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
	printTextDX(getDebugFont(), "mX:", 1100, 0, getMouseX());
	printTextDX(getDebugFont(), "mY:", 1100, 30, getMouseY());

	if (GetKeyboardPress(DIK_LCONTROL)/*��CTRL*/) printList(&xBasedList);//����0518 x�����X�g�̒��g�����o��
	if (GetKeyboardPress(DIK_M)/*�ECTRL*/) printList(&resultList);//����0518 ���ʃ��X�g�̒��g�����o��
	stage.print();//����
};

void unInitializeStage() {
	stage.uninitialize();//����//����0527
	uninitializeEffect(&effectList);//����0527
	uninitializeObjList(&typeCompatList, &xBasedList, &resultList);//����0527
};

void finishStage() {
	finishEffect(&effectList);//����0527
	finishObjList(&typeCompatList, &xBasedList, &resultList);//����0527
};//����0518 ���̃X�e�[�W����߂���ɌĂԊ֐�