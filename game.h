#pragma once
#include "main.h"

enum SceneList {
	TITLE,
	//////////////// îÛè¿í«â¡
	SELECT_MODE,
	CHOOSE_STAGE,
	//////////////// Ç±Ç±Ç‹Ç≈
	STAGE,
	RESULT,
	SCENE_NUM,
};

void initializeGame();
void updateGame();
void drawGame();
void printGame();
void unInitializeGame();
//Å@îÛè¿í«â¡
void changeScene();
int *getScene();
//Å@Ç±Ç±Ç‹Ç≈