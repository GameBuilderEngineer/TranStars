//西川
#include "useList.h"

void checkCheckList(DataList* checkList, TF_List* col, DataList* result);
void checkCollision_updateResult(TF_List* col, DataList* result, ObjStr* x, ObjStr* y);

void checkTypeFunc(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff);
void checkTypeFuncEach(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff);

//初期化↓

void initializeObjList(DataList* data) {
	Initialize(data);
}
void initializeTypeFuncList(TF_List* typeFunc) {
	Initialize(typeFunc);
}

//タイプファンクリストを設定
void setCollisionList(TF_List* typeFunc, objTypes type1, objTypes type2, bool(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFunc(typeFunc, type1, type2, true,FUNC_COLLISION, castFunc(p_func));
}
void setCollisionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	bool(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFuncs(typeFunc, type1L, type1H, type2L, type2H, true, FUNC_COLLISION, castFunc(p_func));
}
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFunc(typeFunc, type1, type2, true, FUNC_ACTION, castFunc(p_func));
}
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b)) {
	setTypeFuncs(typeFunc, type1L, type1H, type2L, type2H, true, FUNC_ACTION, castFunc(p_func));
}
void setActionList(TF_List* typeFunc, objTypes type1, objTypes type2, void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff)) {
	setTypeFunc(typeFunc, type1, type2, true, FUNC_ACTION_EFFECT, castFunc(p_func));
}
void setActionsList(TF_List* typeFunc, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H,
	void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff)) {
	setTypeFuncs(typeFunc, type1L, type1H, type2L, type2H, true, FUNC_ACTION_EFFECT, castFunc(p_func));
}
void optimizeActionList(TF_List* typeFunc) {
	optimizeTypeFuncs(typeFunc);//type1,2に、組み合わせ一緒で順序が逆、同じ関数が登録されてしまうのを避ける
}

//初期化↑

void uninitializeObjList(DataList* data) {
	Terminate(data);
}
void uninitializeTypeFuncList(TF_List* typeFunc) {
	Terminate(typeFunc);
}

//void startObjList(StageClass* stage, DataList* xBased, DataList* result) {
//	for (int i = 0; i < stage->getObjNum(); i++)
//		setObjEdge(xBased, &stage->getObj()[i]);
//		//オブジェクト全ての左端・右端それぞれをノードとしてリストに登録
//}

void finishObjList(DataList* data) {
	Clear(data);
}

//毎フレーム初め、xBasedを維持し、typeFuncが持つfunc(コリジョン判定)をもとにresultを作成
void makeResultList(TF_List* col, DataList* xBased, DataList* result) {
	sortObjEdgeListByX(xBased);//x端リストにオブジェクトの移動を反映

	DataList checkList; Initialize(&checkList);// チェックリスト(xBasedを見る間だけ必要なリスト)作成

	xBased->crnt = xBased->head;// x順リストの着目ノードをリセット
	while (Next(xBased)) {
		if (!xBased->crnt->d._oE.mp_obj->m_use) continue;//useがfalseなら考えない

		if (xBased->crnt->d._oE.mp_L == NULL) {// 調べたオブジェクト端がオブジェクトの左端だった
			InsertRear(&checkList, xBased->crnt->d);//そのオブジェクトをチェックリストに登録(右端は登録しない)

			//チェックリストに新しいオブジェクト端が追加されていないならば
			//リザルトリストに新しいものが増える訳はないので調べ直す必要はない

			checkCheckList(&checkList, col, result);//チェックリストをチェック
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

//既に作った結果リストを、typeFuncListの関数に通す
void checkResultList(TF_List* typeFunc, DataList* result, EffList* eff){
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (result->crnt->d._oC.m_use == true)
			checkTypeFuncEach(typeFunc, result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR, eff);
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
	float size = getObjectHarfSizeLonger(p_obj);//半径と辺、どちらが当たり判定かはともかく長い方
	InsertRearEdges(xBased, p_obj, getObjectFar_PosToCenter(p_obj).x - size, getObjectFar_PosToCenter(p_obj).x + size);
}

//リストの中身を画面に表示
void printList(DataList* draw) {
	Print(draw);
}


//////////////////ローカル

//チェックリストとタイプ相性リストを見つつ、タイプ相性リストに登録された関数の結果を結果リストに記録
void checkCheckList(DataList* checkList, TF_List* col, DataList* result) {
	DataNode *sub_crnt; checkList->crnt = checkList->head;
	while (Next(checkList)) {//リストがダミーのみだったり見終わったら脱出
		sub_crnt = checkList->crnt;
		while (Next(checkList))
			//カレント以前のノードは一つ大きいループで調べ終わっている筈なので比べるのはcrntの次からでよい
			if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj) == NULL)// まだ結果リストにないものだったら
				checkCollision_updateResult(col, result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj);

		checkList->crnt = sub_crnt;//大きいwhileのカレントまで戻す
	}
}

//２つのオブジェクトをタイプリスト(に登録された関数)に通し、結果を結果リストに記録
void checkCollision_updateResult(TF_List* col, DataList* result, ObjStr* x, ObjStr* y) {
	col->crnt = col->head;//タイプ表のカレントをリセット
	while (SearchNextTF_byObjType(col, x->m_type, y->m_type)
		!= NULL)//毎回カレントから出発し、見つかったらカレントを動かす検索。ヘッダに辿り着いたらNULL

			InsertRearCon(result, x, y, (*col->crnt->d.mp_func._b)(x, y));
				// 結果リストにオブジェクトの組み合わせと、それをタイプリスト(の関数)に通して得たbool結果を登録
}

//２つのオブジェクトをタイプ相性リストに登録された関数全てに通す(記録なし)
void checkTypeFunc(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff) {
	typeFunc->crnt = typeFunc->head;//タイプ表のカレントをリセット
	while (SearchNextTF_byObjType(typeFunc, x->m_type, y->m_type)
		!= NULL)//毎回カレントから出発し、見つかったらカレントを動かす検索。ヘッダに辿り着いたらNULL
		if (typeFunc->crnt->d.fType != FUNC_ACTION_EFFECT) (*typeFunc->crnt->d.mp_func._v)(x, y);
		else (*typeFunc->crnt->d.mp_func._ef)(x, y, eff);
}

//x,yを順不同に
void checkTypeFuncEach(TF_List* typeFunc, ObjStr* x, ObjStr* y, EffList* eff) {
	checkTypeFunc(typeFunc, x, y, eff);

	if (x->m_type != y->m_type)//タイプが同じでなければ逆にしてもう一回確かめる
		checkTypeFunc(typeFunc, y, x, eff);
}