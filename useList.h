//西川
#pragma once

#include "main.h"
#include "dataList.h"
#include "StageClass.h"

//起動時
void initializeObjList(DataList* xBased, DataList* result);
void initializeTypeCompatList(DataList* typeCompat, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H
	, bool(*p_func)(ObjStr* a, ObjStr* b)
	, bool optimizeUse);
	//終了時
void uninitializeObjList(DataList* xBased, DataList* result);
void uninitializeTypeCompatList(DataList* typeCompat);
//ステージ開始時、xBased/resultにダミーノードを登録、xBasedにオブジェクトの端を全て登録
void startObjList(StageClass* stage, DataList* xBased, DataList* result);

//ステージ終了時、xBasedとresultを抹消
void finishObjList(DataList* xBased, DataList* result);

//毎フレーム、リストの中身を全て描画
void printList(DataList* draw);

//毎フレーム、xBasedリストの状態を維持、resultリストを削除して作成、及びtypeCompatが覚えている関数を実行して結果のboolを記録
void makeResultList(DataList* typeCompat, DataList* xBased, DataList* result);

void clearResultList(DataList* result);

//毎フレーム、結果リスト(のオブジェクト２つ)を、タイプリスト(の関数)に通す処理
	void checkResultList(DataList* typeCompat,DataList* result);

/*	//結果リストから、funcの結果がfalseなノードを削除
	void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool
	//結果リストの中で、funcの結果がtrueなものをtrueに書き換える
	void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool
	//結果リストの中で、funcの結果がfalseなものをfalseに書き換える
	void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool*/

//オブジェクトの端をx順リストに登録
void setObjEdge(DataList* xBased, ObjStr* p_obj);
