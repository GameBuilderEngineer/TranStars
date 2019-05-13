#pragma once
#include "main.h"

enum SceneList {
	TITLE,
	//////////////// ����ǉ�
	SELECT_MODE,
	CHOOSE_STAGE,
	//////////////// �����܂�
	STAGE,
	RESULT,
	SCENE_NUM,
};

void initializeGame();
void updateGame();
void drawGame();
void printGame();
void unInitializeGame();
//�@����ǉ�
void changeScene();
int *getScene();
//�@�����܂�