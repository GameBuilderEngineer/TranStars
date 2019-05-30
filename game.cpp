#include "game.h"
#include "input.h"
#include "Title.h"
#include "Stage.h"
#include "Result.h"
#include "textureLoader.h"
#include "textWindow.h"

int scene;
TextW textW;

void initializeGame() {
	getTextureLoader()->load(getDevice());//�e�N�X�`���̓Ǎ�
	scene = TITLE;
	initializeTitle();
	initializeStage();
	initializeResult();
	initializeTextW(&textW);//����0530
};

void updateGame() {

	switch (scene)
	{
	case TITLE:		updateTitle();		break;
	case SELECT_MODE: updateTitle(); break;	// ����ǉ�:�V�����V�[�������������́A�^�C�g���̏����Ɋ܂�
	case CHOOSE_STAGE: updateTitle(); break;	// ����ǉ�:�V�����V�[�������������́A�^�C�g���̏����Ɋ܂�
	case STAGE:		updateStage();	changeScene(RESULT)/*����0518*/;break;
	case RESULT:		updateResult();	changeScene(SELECT_MODE)/*����0518*/;break;
	default:	break;
	}
	updateTextW(&textW,GetKeyboardPress(DIK_SPACE));//����0530
};

void drawGame() {
	switch (scene)
	{
	case TITLE:		drawTitle(); break;
	case SELECT_MODE: drawTitle(); break;	// ����ǉ�
	case CHOOSE_STAGE: drawTitle(); break;	// ����ǉ�
	case STAGE:		drawStage(); break;
	case RESULT:		drawResult(); break;
	default:	break;
	}
	drawTextW(&textW);//����0530
};

void printGame()
{
	switch (scene)
	{
	case TITLE:		printTitle(); break;
	case SELECT_MODE:/* drawTitle();*/ break;	// ����ǉ�
	case CHOOSE_STAGE:/* drawTitle();*/ break;	// ����ǉ�
	case STAGE:		printStage(); break;
	case RESULT:	printResult(); break;
	default:	break;
	}
	printTextW(&textW);//����0530
}

void unInitializeGame() {
	getTextureLoader()->release();//�e�N�X�`���̉��
	unInitializeTitle();
	unInitializeStage();
	unInitializeResult();
	uninitializeTextW(&textW);//����0530
};

//void changeScene()
//{
//	{
////		scene++;
////		if (scene >= SCENE_NUM)
////		{
////			scene = 0;
////		}
//		changeNewScene(SceneList(int(scene) + 1));//����0518 �Ӗ��͈ꏏ�̂͂�
//	}
//}

void changeScene(SceneList newscene){
	if (!GetKeyboardTrigger(DIK_RETURN))return;
	scene = newscene;
	if (scene >= SCENE_NUM)
	{
		scene = 0;
	}
	switch (scene)//����0518
	{
	case TITLE: break;
	case SELECT_MODE: break;
	case CHOOSE_STAGE: setTextW(&textW, "�X�e�[�W�I���ł�", 25, 0, 500)/*����0530*/; break;
	case STAGE:	startStage(); break;
	case RESULT: finishStage(); break;
	default:	break;
	}
}//����0518 ++�ȊO�̕��@�ŃV�[���J�� �X�e�[�W�ɓ��钼�O�E����ɂ�������������(����switch��)������̂�game��ʂ����ɃV�[����ς��Ȃ��łق���

// ����ǉ�
int getScene() { return scene; }
// �����܂�