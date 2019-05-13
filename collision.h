
#pragma once
#include "main.h"
#include "object.h"


//オブジェクト同士の当たり判定(円*円)
bool checkHitObjCC(ObjStr* p_obj1, ObjStr* p_obj2);
//オブジェクト同士の当たり判定(矩形*矩形)
bool checkHitObjRR(ObjStr* p_obj1, ObjStr* p_obj2);
//オブジェクト同士の当たり判定(円*矩形)
bool checkHitObjCR(ObjStr* p_obj1, ObjStr* p_obj2);

// 回転している矩形の頂点を計算
D3DXVECTOR2 computeRotatedBox(ObjStr* p_obj);
