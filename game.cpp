#include "game.h"
#include "input.h"
#include "Title.h"
#include "Stage.h"
#include "Result.h"
#include "textureLoader.h"

int scene;
void changeScene();

void initializeGame() {
	getTextureLoader()->load(getDevice());//テクスチャの読込
	scene = TITLE;
	initializeTitle();
	initializeStage();
	initializeResult();
};

void updateGame() {
	
	switch (scene)
	{
	case TITLE:		updateTitle();		break;
	case SELECT_MODE: updateTitle(); break;	// 樋沼追加
	case CHOOSE_STAGE: updateTitle(); break;	// 樋沼追加
	case STAGE:		updateStage();	break;
	case RESULT:		updateResult();	break;
	default:	break;
	}
};

void drawGame() {
	switch (scene)
	{
	case TITLE:		drawTitle(); break;
	case SELECT_MODE: drawTitle(); break;	// 樋沼追加
	case CHOOSE_STAGE: drawTitle(); break;	// 樋沼追加
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
	case SELECT_MODE: drawTitle(); break;	// 樋沼追加
	case CHOOSE_STAGE: drawTitle(); break;	// 樋沼追加
	case STAGE:		printStage(); break;
	case RESULT:		printResult(); break;
	default:	break;
	}
}

void unInitializeGame() {
	getTextureLoader()->release();//テクスチャの解放
	unInitializeTitle();
	unInitializeStage();
	unInitializeResult();
};

void changeScene()
{
	if(GetKeyboardTrigger(DIK_RETURN))
	{
		scene++;
		if (scene >= SCENE_NUM)
		{
			scene = 0;
		}
	}
}

// 樋沼追加
int *getScene() { return (&scene); }
// ここまで