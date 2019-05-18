#pragma once
#include "main.h"

enum SceneList {
	TITLE,
	//////////////// 樋沼追加
	SELECT_MODE,
	CHOOSE_STAGE,
	//////////////// ここまで
	STAGE,
	RESULT,
	SCENE_NUM,
};

void initializeGame();
void updateGame();
void drawGame();
void printGame();
void unInitializeGame();
//　樋沼追加
void changeScene();
int *getScene();
//　ここまで

void changeNewScene(SceneList newscene);//西川0518 ++以外の方法でシーン遷移 ステージに入る直前・直後にだけしたい処理があるのでgameを通さずにシーンを変えないでほしい
