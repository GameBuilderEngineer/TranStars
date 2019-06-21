#pragma once

#include "main.h"
#include "effect.h"//����0530 �G�t�F�N�g
#include "StageClass.h"
#include "DynamicClass.h"
#include "comet.h"

void initializeStage();
void startStage();//����0518 �V�����X�e�[�W�ɓ���O�ɌĂԊ֐�
void updateStage();
void drawStage();
void printStage();
void unInitializeStage();
void finishStage();//����0518 �V�����X�e�[�W�ɓ���O�ɌĂԊ֐�

void setxBased(ObjStr* obj);
EffList* getEffect();//����0530
StageClass* getStageClass();//����0531
DynamicClass* getCometClass();
DynamicClass* getStarClass();