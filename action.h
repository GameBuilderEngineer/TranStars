#pragma once
#include "object.h"
#include "effect.h"

//２つのオブジェクトに対してやる処理を書く

void actFitStar(ObjStr* star, ObjStr* frame, EffList* eff);
void actSplit(ObjStr* collisionObject, ObjStr* stardust, EffList* eff);
void actReflect(ObjStr* collisionObject, ObjStr* reflection);
