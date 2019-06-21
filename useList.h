//西川
#pragma once

#include "main.h"
#include "dataList.h"
#include "funcTypeList.h"
#include "StageClass.h"

//起動時
void initializeObjList(DataList* data);
void initializeTypeFuncList(TF_List* typeFunc);

void setCollisionList(TF_List* typeFunc, objTypes type1, objTypes type2, bool(*p_func)(ObjStr* a, ObjStr* b));
void setCollisionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	bool(*p_func)(ObjStr* a, ObjStr* b));
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b));
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b));
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff));
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff));

void optimizeActionList(TF_List* typeFunc);
//終了時
void uninitializeObjList(DataList* data);
void uninitializeTypeFuncList(TF_List* typeFunc);

//ステージ開始時、xBasedにオブジェクトの端を全て登録
//void startObjList(StageClass* stage, DataList* xBased, DataList* result);
//ステージ終了時、xBasedとresultの中身を空に
void finishObjList(DataList* data);

//毎フレーム、リストの中身を全て描画
void printList(DataList* draw);

//毎フレーム初め、xBasedを維持し、typeFuncが持つfunc(コリジョン判定)をもとにresultを作成
void makeResultList(TF_List* col, DataList* xBased, DataList* result);
//前のフレームのコリジョン結果を消去
void clearResultList(DataList* result);

//毎フレーム、結果リスト(のオブジェクト２つ)を、タイプリスト(の関数)に通す処理
void checkResultList(TF_List* typeFunc, DataList* result, EffList* eff);

/*
//結果リストから、funcの結果がfalseなノードを削除
void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool
//結果リストの中で、funcの結果がtrueなものをtrueに書き換える
void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool
//結果リストの中で、funcの結果がfalseなものをfalseに書き換える
void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool
*/

//オブジェクトの端をx順リストに登録
void setObjEdge(DataList* xBased, ObjStr* p_obj);
