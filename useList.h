//西川
#pragma once

#include "main.h"
#include "dataList.h"

//ステージ開始時、xBased/resultにダミーノードを登録、xBasedにオブジェクトの端を全て登録
void initializeObjList(StageObj* p_stageobj, DataList* xBased, DataList* result);
//ステージ終了時、xBasedとresultを抹消
void uninitializeObjList(DataList* xBased, DataList* result);

//毎フレーム、xBasedリストの状態を維持、resultリストを作成、及びprocess(よそからもらった処理)を実行して結果のboolを記録
void updateObjList(DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b));
//毎フレーム、既に作った結果リストを全部見回る処理(不都合が出そうなので出たときは変えます)
	void checkResultList(DataList* result, void process(ObjStr* a, ObjStr* b));//戻り値なし
	//結果リストから、processの結果がfalseなノードを削除
	void check_cutResultList(DataList* result, bool process(ObjStr* a, ObjStr* b));//戻り値bool
	//結果リストの中で、processの結果がtrueなものをtrueに書き換える
	void check_updateOrResultList(DataList* result, bool process(ObjStr* a, ObjStr* b));//戻り値bool
	//結果リストの中で、processの結果がfalseなものをfalseに書き換える
	void check_updateAndResultList(DataList* result, bool process(ObjStr* a, ObjStr* b));//戻り値bool



//毎フレーム、リストの中身を全て描画
void printList(DataList* draw);
