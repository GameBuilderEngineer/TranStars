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
	getTextureLoader()->load(getDevice());//テクスチャの読込
	scene = TITLE;
	initializeTitle();
	initializeStage();
	initializeSelect();
	initializeResult();
	initializeTextW(&textW);//西川0530
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
	//updateTextW(&textW,GetKeyboardPress(DIK_SPACE));//西川0530
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
	//drawTextW(&textW);//西川0530
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
	//printTextW(&textW);//西川0530
}

void unInitializeGame() {
	getTextureLoader()->release();//テクスチャの解放
	unInitializeSelect();
	unInitializeTitle();
	unInitializeStage();
	unInitializeResult();
	uninitializeTextW(&textW);//西川0530
};

void changeScene(SceneList newscene){
	scene = newscene;
	if (scene >= SCENE_NUM)
	{
		scene = 0;
	}
	switch (scene)//西川0518
	{
	case TITLE: break;
	case SELECT:releaseTextW(&textW); setTextW(&textW, "ステージ選択です", 25, 0, 500)/*西川0530*/; break;
	case STAGE:releaseTextW(&textW); startStage(); break;
	case RESULT: finishStage(); break;
	default:	break;
	}
}//西川0518 ++以外の方法でシーン遷移 ステージに入る直前・直後にだけしたい処理(↑のswitch内)があるのでgameを通さずにシーンを変えないでほしい

int getScene() { return scene; }