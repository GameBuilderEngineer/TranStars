//西川
#include "useList.h"

void checkCheckList(DataList* checkList, DataList* typeCompat, DataList* result);
void checkTypeCompat_updateResult(DataList* typeCompat, DataList* result, ObjStr* x, ObjStr* y);
void checkTypeCompat(DataList* typeCompat, ObjStr* x, ObjStr* y);

void initializeObjList(DataList* xBased, DataList* result) {
	Initialize(xBased);
	Initialize(result);
}
void initializeTypeCompatList(DataList* typeCompat, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H
	, bool(*p_func)(ObjStr* a, ObjStr* b)
	, bool optimizeUse) {
	Initialize(typeCompat);
	setTypeCompats(typeCompat, type1L, type1H, type2L, type2H, true, p_func);
	if (optimizeUse)
		optimizeTypeCompats(typeCompat);
}
void uninitializeObjList(DataList* xBased, DataList* result) {
	Terminate(xBased);
	Terminate(result);
}
void uninitializeTypeCompatList(DataList* typeCompat) {
	Terminate(typeCompat);
}

void startObjList(StageClass* stage, DataList* xBased, DataList* result) {
	for (int i = 0; i < stage->getObjNum(); i++) {
		setObjEdge(xBased, &stage->getObj()[i]);
		//オブジェクト全ての左端・右端それぞれをノードとしてリストに登録
	}
}


void finishObjList(DataList* xBased, DataList* result) {
	Clear(xBased);
	Clear(result);
}

//毎フレーム、xBasedを維持し、typeCompatが持つfuncをもとにresultを作成
void makeResultList(DataList* typeCompat, DataList* xBased, DataList* result) {
	sortObjEdgeListByX(xBased);//x端リストにオブジェクトの移動を反映

	DataList checkList; Initialize(&checkList);// チェックリスト(xBasedを見る間だけ必要なリスト)作成

	xBased->crnt = xBased->head;// x順リストの着目ノードをリセット
	while (Next(xBased)) {
		if (!xBased->crnt->d._oE.mp_obj->m_use) continue;//useがfalseなら考えない

		if (xBased->crnt->d._oE.mp_L == NULL) {// 調べたオブジェクト端がオブジェクトの左端だった
			InsertRear(&checkList, xBased->crnt->d);//そのオブジェクトをチェックリストに登録(右端は登録しない)

			//チェックリストに新しいオブジェクト端が追加されていないならば
			//リザルトリストに新しいものが増える訳はないので調べ直す必要はない

			checkCheckList(&checkList, typeCompat, result);//チェックリストをチェック
		}
		if (xBased->crnt->d._oE.mp_L != NULL) {// 調べたオブジェクト端がオブジェクトの右端だった
			checkList.crnt = SearchObjEdge(&checkList, xBased->crnt->d._oE.mp_L->mp_obj);
			RemoveCurrent(&checkList);
			// 右端まで来たので、対応する左端ノードをチェックリストから探して消す
			// NULLであることはない筈
		}
	}

	Terminate(&checkList);//チェックリスト撲滅
}

void clearResultList(DataList* result) {
	Clear(result);//毎フレーム、前のresultを(要らない＋次作るまでに消しとかなきゃいけないので)消去
}

//既に作った結果リストを全部funcで参照する
void checkResultList(DataList* typeCompat, DataList* result){
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (result->crnt->d._oC.m_use==true) checkTypeCompat(typeCompat, result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}

/*
//結果リストから、funcの結果がfalseなノードを削除
void cutResultList(DataList* result, bool func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (!func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR)) RemoveCurrent(result);
}
//結果リストの中で、funcの結果がtrueなものをtrueに書き換える
void updateOrResultList(DataList* result, bool func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (!result->crnt->d._oC.m_use) result->crnt->d._oC.m_use = func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}
//結果リストの中で、funcの結果がfalseなものをfalseに書き換える
void updateAndResultList(DataList* result, bool func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (result->crnt->d._oC.m_use) result->crnt->d._oC.m_use = func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}*/

//オブジェクトの端をx順リストに登録
void setObjEdge(DataList* xBased, ObjStr* p_obj) {
	float size = getObjectSizeLonger(p_obj);//半径と辺、どちらが当たり判定かはともかく長い方
	InsertRearEdges(xBased, p_obj, p_obj->m_image.width / 2.0f - size, p_obj->m_image.width / 2.0f + size);
}

//リストの中身を画面に表示
void printList(DataList* draw) {
	Print(draw);
}


//////////////////ローカル

//チェックリストとタイプ相性リストを見つつ、タイプ相性リストに登録された関数の結果を結果リストに記録
void checkCheckList(DataList* checkList, DataList* typeCompat, DataList* result) {
	DataNode *sub_crnt; checkList->crnt = checkList->head;
	while (Next(checkList)) {//リストがダミーのみだったり見終わったら脱出
		sub_crnt = checkList->crnt;
		while (Next(checkList))
			//カレント以前のノードは一つ大きいループで調べ終わっている筈なので比べるのはcrntの次からでよい
			if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj) == NULL)// まだ結果リストにないものだったら
				checkTypeCompat_updateResult(typeCompat, result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj);
		checkList->crnt = sub_crnt;//大きいwhileのカレントまで戻す
	}
}

//２つのオブジェクトをタイプリスト(に登録された関数)に通し、結果を結果リストのカレントに記録
void checkTypeCompat_updateResult(DataList* typeCompat, DataList* result, ObjStr* x, ObjStr* y) {
	typeCompat->crnt = typeCompat->head;//タイプ表のカレントをリセット
	while (SearchNextTypeCompat(typeCompat, x->m_type, y->m_type)
		!= NULL)//毎回カレントから出発し、見つかったらカレントを動かす検索。ヘッダに辿り着いたらNULL

			InsertRearCon(result, x, y, (*typeCompat->crnt->d._tC.mp_func)(x, y));
				// 結果リストにオブジェクトの組み合わせと、それをタイプリスト(の関数)に通して得た結果を登録
}

//２つのオブジェクトをタイプ相性リストに登録された関数全てに通す(記録なし)
void checkTypeCompat(DataList* typeCompat, ObjStr* x, ObjStr* y) {
	typeCompat->crnt = typeCompat->head;//タイプ表のカレントをリセット
	while (SearchNextTypeCompat(typeCompat, x->m_type, y->m_type)
		!= NULL)//毎回カレントから出発し、見つかったらカレントを動かす検索。ヘッダに辿り着いたらNULL
		(*typeCompat->crnt->d._tC.mp_func)(x, y);
	if (x->m_type != y->m_type) {//両方確かめる
		typeCompat->crnt = typeCompat->head;//タイプ表のカレントをリセット
		while (SearchNextTypeCompat(typeCompat, y->m_type, x->m_type)
			!= NULL)//毎回カレントから出発し、見つかったらカレントを動かす検索。ヘッダに辿り着いたらNULL
			(*typeCompat->crnt->d._tC.mp_func)(y, x);
	}

}