#pragma once
#include "object.h"

const float VALUE_ATTRACTION = 0.2f; // 引力の強さ
const float RANGE_ATTRACTION = 800.0f;	// 引力の働く範囲

void initializeBlackHole(ObjStr* blackHole, ObjStr* others,int targetNum);
void setBlackHole(ObjStr* blackHole);
void updateBlackHole(ObjStr* blackHole);

void attractObject(ObjStr* object, ObjStr*blackHole);
void sendObject(ObjStr* collisionObject, ObjStr* blackHole);