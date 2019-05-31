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
TextW textW;

void initializeGame() {
	getTextureLoader()->load(getDevice());//�e�N�X�`���̓Ǎ�
	scene = TITLE;
	initializeTitle();
	initializeStage();
	initializeSelect();
	initializeResult();
	initializeTextW(&textW);//����0530
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
	//updateTextW(&textW,GetKeyboardPress(DIK_SPACE));//����0530
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
	//drawTextW(&textW);//����0530
};

void printGame()
{
#ifdef _DEBUG
	switch (scene)
	{
	case TITLE:		printTitle(); break;
	case SELECT:	printSelect(); break;
	case STAGE:		printStage(); break;
	case RESULT:	printResult(); break;
	default:	break;
	}
#endif // DEBUG
	//printTextW(&textW);//����0530
}

void unInitializeGame() {
	getTextureLoader()->release();//�e�N�X�`���̉��
	unInitializeSelect();
	unInitializeTitle();
	unInitializeStage();
	unInitializeResult();
	uninitializeTextW(&textW);//����0530
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
	case SELECT:releaseTextW(&textW); setTextW(&textW, "�X�e�[�W�I���ł�", 25, 0, 500)/*����0530*/; break;
	case STAGE:releaseTextW(&textW); startStage(); break;
	case RESULT: finishStage(); break;
	default:	break;
	}
}//����0518 ++�ȊO�̕��@�ŃV�[���J�� �X�e�[�W�ɓ��钼�O�E����ɂ�������������(����switch��)������̂�game��ʂ����ɃV�[����ς��Ȃ��łق���

int getScene() { return scene; }