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