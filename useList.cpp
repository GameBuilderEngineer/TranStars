//西川
#include "useList.h"

void optimizeObjList_getResult(DataList* compat, DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b));

void initializeObjList(StageObj* p_stageobj, DataList* xBased, DataList* result) {
	Initialize(xBased);
	for (int i = 0; i < p_stageobj->m_OBJNUM; i++) {
		float size = getObjectSizeLonger(&p_stageobj->m_Obj[i]);//半径と辺、どちらが当たり判定かはともかく長い方
		InsertRearEdges(xBased, &p_stageobj->m_Obj[i],
			p_stageobj->m_Obj[i].m_image.width / 2.0f - size, p_stageobj->m_Obj[i].m_image.width / 2.0f + size);
		//オブジェクト全ての左端・右端それぞれをノードとしてリストに登録
	}
	Initialize(result);
}
void uninitializeObjList(DataList* xBased, DataList* result) {
	Terminate(xBased);
	Terminate(result);
}

void updateObjList(DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b)) {
	Clear(result);//毎フレーム、前のresultを(要らない＋次作るまでに消しとかなきゃいけないので)消去
	sortObjEdgeListByX(xBased);//x端リストにオブジェクトの移動を反映
	optimizeObjList_getResult(NULL, xBased, result, process);
}

//既に作った結果リストを全部processで参照する
void checkResultList(DataList* result, void process(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		process(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}
//結果リストから、processの結果がfalseなノードを削除
void check_cutResultList(DataList* result, bool process(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (!process(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR)) RemoveCurrent(result);
}
//結果リストの中で、processの結果がtrueなものをtrueに書き換える
void check_updateOrResultList(DataList* result, bool process(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (!result->crnt->d._oC.m_use) result->crnt->d._oC.m_use = process(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}
//結果リストの中で、processの結果がfalseなものをfalseに書き換える
void check_updateAndResultList(DataList* result, bool process(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		if (result->crnt->d._oC.m_use) result->crnt->d._oC.m_use = process(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}

//リストの中身を画面に表示
void printList(DataList* draw) {
	Print(draw);
}

//毎フレーム、xBasedとprocess(なんらかの処理)をもとにresultを作成
void optimizeObjList_getResult(DataList* compat, DataList* xBased, DataList* result, bool process(ObjStr* a, ObjStr* b)) {

	//compatとは？…タイプ関係。余裕があったらタイプ関係による効率化もしたい

	DataList checkList; Initialize(&checkList);// チェックリスト(xBasedを見る間だけ必要なリスト)作成

	xBased->crnt = xBased->head;// x順リストの着目ノードをリセット
	while (Next(xBased)) {
		if (xBased->crnt->d._oE.mp_L == NULL) {// 調べたオブジェクト端がオブジェクトの左端だった
			InsertRear(&checkList, xBased->crnt->d);//そのオブジェクトをチェックリストに登録(右端は登録しない)

			//チェックリストに新しいオブジェクト端が追加されていないならば
			//リザルトリストに新しいものが増える訳はないので調べ直す必要はない
			DataNode *sub_crnt; checkList.crnt = checkList.head;
			while (Next(&checkList)) {//リストがダミーのみだったり見終わったら脱出
				sub_crnt = checkList.crnt;
				while (Next(&checkList)) {
					//カレント以前のノードは一つ大きいループで調べ終わっている筈なので比べるのはcrntの次からでよい
					if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList.crnt->d._oE.mp_obj) == NULL)
						InsertRearCon(result, sub_crnt->d._oE.mp_obj, checkList.crnt->d._oE.mp_obj,
							// まだ結果リストにないものだったら結果リストに登録
							process(sub_crnt->d._oE.mp_obj, checkList.crnt->d._oE.mp_obj));
					// もらった関数で得た結果(bool型)も登録
				}
				checkList.crnt = sub_crnt;//カレントまで戻す
			}
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
