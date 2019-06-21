#pragma once

#include "main.h"
#include "effect.h"//西川0530 エフェクト
#include "StageClass.h"
#include "DynamicClass.h"
#include "comet.h"

void initializeStage();
void startStage();//西川0518 新しいステージに入る前に呼ぶ関数
void updateStage();
void drawStage();
void printStage();
void unInitializeStage();
void finishStage();//西川0518 新しいステージに入る前に呼ぶ関数

void setxBased(ObjStr* obj);
EffList* getEffect();//西川0530
StageClass* getStageClass();//西川0531
DynamicClass* getCometClass();
DynamicClass* getStarClass();