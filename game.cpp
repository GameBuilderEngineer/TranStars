#include "game.h"
#include "input.h"
#include "Title.h"
#include "Stage.h"
#include "Result.h"
#include "textureLoader.h"

int scene;
//void changeScene();//西川0518

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
	case STAGE:		updateStage();	changeScene()/*西川0518*/;break;
	case RESULT:		updateResult();	changeScene()/*西川0518*/;break;
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
//		scene++;
//		if (scene >= SCENE_NUM)
//		{
//			scene = 0;
//		}
		changeNewScene(SceneList(int(scene) + 1));//西川0518 意味は一緒のはず
	}
}

void changeNewScene(SceneList newscene){
	scene = newscene;
	if (scene >= SCENE_NUM)
	{
		scene = 0;
	}
	switch (scene)//西川0518
	{
	case TITLE: break;
	case STAGE:	startStage(); break;
	case RESULT: finishStage(); break;
	default:	break;
	}
}//西川0518 ++以外の方法でシーン遷移 ステージに入る直前・直後にだけしたい処理(↑のswitch内)があるのでgameを通さずにシーンを変えないでほしい

// 樋沼追加
int *getScene() { return (&scene); }
// ここまで