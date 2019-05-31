#include "game.h"
#include "input.h"
#include "Title.h"
#include "Stage.h"
#include "Select.h"
#include "Result.h"
#include "textureLoader.h"
#include "textWindow.h"

int scene;
bool doChangeScene = false;
void initializeGame() {
	getTextureLoader()->load(getDevice());//�e�N�X�`���̓Ǎ�
	scene = TITLE;
	initializeTitle();
	initializeStage();
	initializeSelect();
	initializeResult();
};

void updateGame() {
	switch (scene)
	{
	case TITLE:		updateTitle();	break;
	case SELECT:	updateSelect();	break;
	case STAGE:		updateStage();break;
	case RESULT:	updateResult();break;
	default:	break;
	}
};

void drawGame() {
	switch (scene)
	{
	case TITLE:		drawTitle(); break;
	case SELECT:	drawSelect(); break;
	case STAGE:		drawStage(); break;
	case RESULT:	drawResult(); break;
	default:	break;
	}
};

void printGame()
{
#if 0
	switch (scene)
	{
	case TITLE:		printTitle(); break;
	case SELECT:	printSelect(); break;
	case STAGE:		printStage(); break;
	case RESULT:	printResult(); break;
	default:	break;
	}
	printTextW();//����0528
#endif
}

void unInitializeGame() {
	getTextureLoader()->release();//�e�N�X�`���̉��
	unInitializeSelect();
	unInitializeTitle();
	unInitializeStage();
	unInitializeResult();
//	uninitializeTextW();//����0528
};

void changeScene(SceneList newscene){
	scene = newscene;
	if (scene >= SCENE_NUM)
	{
		scene = 0;
	}
	switch (scene)//����0518
	{
	case TITLE: break;
	case SELECT: break;
	case STAGE:	startStage(); break;
	case RESULT: finishStage(); break;
	default:	break;
	}
}//����0518 ++�ȊO�̕��@�ŃV�[���J�� �X�e�[�W�ɓ��钼�O�E����ɂ�������������(����switch��)������̂�game��ʂ����ɃV�[����ς��Ȃ��łق���

int getScene() { return scene; }