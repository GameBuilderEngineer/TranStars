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
int getScene();//�|�C���^���擾���āA���ڃV�[����ς���͖̂����ŁBkanno
