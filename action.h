#pragma once
#include "object.h"
#include "effect.h"

//２つのオブジェクトに対してやる処理を書く

void actFitSmallStar(ObjStr* smallstar, ObjStr* smallframe, EffList* eff);
void actFitBigStar(ObjStr* bigstar, ObjStr* bigframe, EffList* eff);

void actSplit(ObjStr* collisionObject, ObjStr* stardust, EffList* eff);
void actReflect(ObjStr* collisionObject, ObjStr* reflection);
