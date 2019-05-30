//stage�V�[��
#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include "textureLoader.h"
#include "object.h"
#include "Select_Game.h" // ����ǉ�
#include "useList.h"//����0530
#include "collision.h"//����0530 �R���W�������̊֐������X�g�ɓn������
#include "effect.h"//����0530 �G�t�F�N�g
#include "StageClass.h"
#include "BlackHole.h"

StageClass stage;//�X�e�[�W�ʃf�[�^

Image gameBG;
DataList collTypeList;//����0530 �R���W�����p �^�C�v�֌W�Ǝ��s����֐��̃��X�g(initialize�ō���ăQ�[�����ʗp)
DataList actTypeList;//����0530 �A�N�V�����p �^�C�v���X�g(�ʗp)
DataList xBasedList;//����0518 x���W�� �I�u�W�F�N�g���X�g(�ʗp)
DataList resultList;//����0518 �m���ߌ��� �I�u�W�F�N�g�֌W���X�g(update�Ŗ��t���[������Ďg���̂�)
EffList effectList;//����0525 �G�t�F�N�g�������������X�g(�ʗp)

ObjStr blackHole;//�u���b�N�z�[��
ObjStr whiteHole;//�z���C�g�z�[��
ObjStr cursor;//�J�[�\��
ObjStr* star = NULL;//���ւ̃|�C���^[]���I�z��p
ObjStr* comet = NULL;//覐΂ւ̃|�C���^[]���I�z��p


void initializeStage() {
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
	initializeObjList(&xBasedList, &resultList);//����0527
	initializeTypeCompatList(&collTypeList, NO_TYPE, TYPE_MAX, NO_TYPE, TYPE_MAX, &checkHitObjCC, false);
	initializeTypeCompatList(&actTypeList, CHARA_SMALL_STAR, TYPE_MAX, CHARA_BLACKHOLE, CHARA_BLACKHOLE, &sendObject, false);
	initializeEffect(&effectList);//����0527
};

void startStage() {	
	//�X�e�[�W�Z���N�g�ŁA�X�e�[�W�ϐ����珉��������悤�ɂ���:�Ƃ肠�����X�e�[�W�P
	stage.initialize(stageNS::STAGE01);//����
	initializeObject(&whiteHole, 10000, CHARA_WHITEHOLE, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
	initializeObject(&blackHole, 10000, CHARA_BLACKHOLE, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
	initializeObject(&cursor, 10000, UI_CURSOR, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());

	setWhiteHole(&blackHole, &whiteHole);

	//initializeObject(&cursor, 10000, UI_CURSOR, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
	//initializeObject(&cursor, 10000, UI_CURSOR, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());

	startEffect(&effectList);//����0527
	startObjList(&stage, &xBasedList, &resultList);//����0527

	setObjEdge(&xBasedList, &blackHole);

};//����0518 �V�����X�e�[�W�ɓ���O�ɌĂԊ֐�

void updateStage() {
	clearResultList(&resultList);//	�O�t���[���̌��ʃ��X�g��p��

	// ����ǉ�
	// timer��main�ɂ��邩��A������if�����邩�A������timer�������Ă��邩�ǂ��炪������
	// ���V����Timer�N���X�̃C���X�^���X���쐬����Ɨǂ��Ǝv���܂��B

	bool p_pause = *getPause();
	updatePause();
	// ��̂����܂�
	stage.update();//����
	updateObject(&whiteHole);
	updateObject(&blackHole);
	updateObject(&cursor);
	
	if (getMouseLButtonTrigger())
		makeParticle(&effectList, { (float)getMouseX(), (float)getMouseY() });//����0525
	if (getMouseRButtonTrigger())
//		makeMagic(&effectList, { (float)getMouseX(), (float)getMouseY() });//����0526
		makeSplit(&effectList, { (float)getMouseX(), (float)getMouseY() }, stage.getObj()[0].m_image);//����0527
	makeEffect(&effectList, eTAIL, &stage.getObj()[3]);//����0528
	updateEffect(&effectList);//����0525

	makeResultList(&collTypeList, &xBasedList, &resultList);//����0527 x�����X�g���X�V�A�����i�s�I�ɃR���W�����֐��̓������^�C�v���X�g��n���Č��ʃ��X�g�擾
	checkResultList(&actTypeList, &resultList);//����0530
};

void drawStage() {
	DrawImage(&gameBG);
	drawEffect(&effectList);//����0530�I�u�W�F�N�g����ɕ`��

	stage.draw();//����
	drawObject(&whiteHole);
	drawObject(&blackHole);
	drawObject(&cursor);

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
	printObject(&whiteHole);
	printObject(&blackHole);
	printObject(&cursor);
};

void unInitializeStage() {
	stage.uninitialize();//����//����0527
	uninitializeEffect(&effectList);//����0527
	uninitializeObjList(&xBasedList, &resultList);//����0527
	uninitializeTypeCompatList(&collTypeList);//����0530
	uninitializeTypeCompatList(&actTypeList);//����0530
};

void finishStage() {
	finishEffect(&effectList);//����0527
	finishObjList(&xBasedList, &resultList);//����0527
};//����0518 ���̃X�e�[�W����߂���ɌĂԊ֐�
