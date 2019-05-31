#pragma once

#include "main.h"
#include "effect.h"//西川0530 エフェクト

void initializeStage();
void startStage();//西川0518 新しいステージに入る前に呼ぶ関数
void updateStage();
void drawStage();
void printStage();
void unInitializeStage();
void finishStage();//西川0518 新しいステージに入る前に呼ぶ関数

EffList* getEffect();//西川0530