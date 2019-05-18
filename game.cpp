#include "game.h"
#include "input.h"
#include "Title.h"
#include "Stage.h"
#include "Result.h"
#include "textureLoader.h"

int scene;
//void changeScene();//����0518

void initializeGame() {
	getTextureLoader()->load(getDevice());//�e�N�X�`���̓Ǎ�
	scene = TITLE;
	initializeTitle();
	initializeStage();
	initializeResult();
};

void updateGame() {

	switch (scene)
	{
	case TITLE:		updateTitle();		break;
	case SELECT_MODE: updateTitle(); break;	// ����ǉ�
	case CHOOSE_STAGE: updateTitle(); break;	// ����ǉ�
	case STAGE:		updateStage();	changeScene()/*����0518*/;break;
	case RESULT:		updateResult();	changeScene()/*����0518*/;break;
	default:	break;
	}
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
};

void printGame()
{
	switch (scene)
	{
	case TITLE:		printTitle(); break;
	case SELECT_MODE: drawTitle(); break;	// ����ǉ�
	case CHOOSE_STAGE: drawTitle(); break;	// ����ǉ�
	case STAGE:		printStage(); break;
	case RESULT:		printResult(); break;
	default:	break;
	}
}

void unInitializeGame() {
	getTextureLoader()->release();//�e�N�X�`���̉��
	unInitializeTitle();
	unInitializeStage();
	unInitializeResult();
};

void changeScene()
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{
//		scene++;
//		if (scene >= SCENE_NUM)
//		{
//			scene = 0;
//		}
		changeNewScene(SceneList(int(scene) + 1));//����0518 �Ӗ��͈ꏏ�̂͂�
	}
}

void changeNewScene(SceneList newscene){
	scene = newscene;
	if (scene >= SCENE_NUM)
	{
		scene = 0;
	}
	switch (scene)//����0518
	{
	case TITLE: break;
	case STAGE:	startStage(); break;
	case RESULT: finishStage(); break;
	default:	break;
	}
}//����0518 ++�ȊO�̕��@�ŃV�[���J�� �X�e�[�W�ɓ��钼�O�E����ɂ�������������(����switch��)������̂�game��ʂ����ɃV�[����ς��Ȃ��łق���

// ����ǉ�
int *getScene() { return (&scene); }
// �����܂�