#pragma once
#include "object.h"

const float VALUE_ATTRACTION = 0.2f; // ���͂̋���
const float RANGE_ATTRACTION = 800.0f;	// ���͂̓����͈�

void initializeBlackHole(ObjStr* blackHole, ObjStr* others,int targetNum);
void setBlackHole(ObjStr* blackHole);
void updateBlackHole(ObjStr* blackHole);

void attractObject(ObjStr* object, ObjStr*blackHole);
void sendObject(ObjStr* collisionObject, ObjStr* blackHole);