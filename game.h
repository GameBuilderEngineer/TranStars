#pragma once
#include "main.h"

enum SceneList {
	TITLE,
	SELECT,
	STAGE,
	RESULT,
	SCENE_NUM,
};

void initializeGame();
void updateGame();
void drawGame();
void printGame();
void unInitializeGame();
void changeScene(SceneList newscene);
int getScene();//ポインタを取得して、直接シーンを変えるのは無しで。kanno
