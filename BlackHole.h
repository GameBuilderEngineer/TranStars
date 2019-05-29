#pragma once
#include "object.h"

const float VALUE_ATTRACTION = 0.7f; // ˆø—Í‚Ì‹­‚³
const float RANGE_ATTRACTION = 800.0f;	// ˆø—Í‚Ì“­‚­”ÍˆÍ

void initializeBlackHole(ObjStr* blackHole, ObjStr* others,int targetNum);
void setBlackHole(ObjStr* blackHole);
void updateBlackHole(ObjStr* blackHole);