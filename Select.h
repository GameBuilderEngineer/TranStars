// îÛè¿í«â¡
#pragma once

#include "main.h"

enum MENU_LIST
{
	NEW_GAME,
	CHOOSE_STAGE,
	MENU_NUM
};

enum STAGE_LIST
{
	STAGE01,
	STAGE02,
	STAGE03,
	STAGE04,
	STAGE05,
	STAGE06,
	STAGE07,
	STAGE08,
	STAGE09,
	STAGE10,
	STAGE11,
	STAGE12,
	STAGE_NUM,
};


void initializeSelect();
void updateSelect();
void drawSelect();
void printSelect();
void unInitializeSelect();
int getSelectStage();