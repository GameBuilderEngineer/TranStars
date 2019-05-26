//西川
#pragma once

#include "main.h"
#include "dataList.h"
#include "StageClass.h"

//ステージ開始時、xBased/resultにダミーノードを登録、xBasedにオブジェクトの端を全て登録
void initializeObjList(StageClass* stage, DataList* xBased, DataList* result);
//void setTypeList(DataList* typeCompat, objTypes type1, objTypes type2, bool act, bool pas, bool (*func)(ObjStr* a, ObjStr* b));
//ステージ終了時、xBasedとresultを抹消
void uninitializeObjList(DataList* xBased, DataList* result);

//毎フレーム、xBasedリストの状態を維持、resultリストを作成、及びfunc(よそからもらった処理)を実行して結果のboolを記録
void updateObjList(DataList* xBased, DataList* result, bool func(ObjStr* a, ObjStr* b));
//毎フレーム、既に作った結果リストを全部見回る処理(不都合が出そうなので出たときは変えます)
	void checkResultList(DataList* result, void func(ObjStr* a, ObjStr* b));//戻り値なし
	//結果リストから、funcの結果がfalseなノードを削除
	void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool
	//結果リストの中で、funcの結果がtrueなものをtrueに書き換える
	void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool
	//結果リストの中で、funcの結果がfalseなものをfalseに書き換える
	void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b));//戻り値bool



//毎フレーム、リストの中身を全て描画
void printList(DataList* draw);
