#pragma once
#include "object.h"
#include "effect.h"

//�Q�̃I�u�W�F�N�g�ɑ΂��Ă�鏈��������

void actFitSmallStar(ObjStr* smallstar, ObjStr* smallframe, EffList* eff);
void actFitBigStar(ObjStr* bigstar, ObjStr* bigframe, EffList* eff);

void actSplit(ObjStr* collisionObject, ObjStr* stardust, EffList* eff);
void actReflect(ObjStr* collisionObject, ObjStr* reflection);
