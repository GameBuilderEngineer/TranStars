//西川
#include "useList.h"
#include "collision.h"//西川0527 コリジョン内の関数をリストに渡すため
#include "effect.h"//西川0527 エフェクト
#include "BlackHole.h"//西川0527 エフェクト

void optimizeObjList_getResult(DataList* typeCompat, DataList* xBased, DataList* result);
void checkCheckList(DataList* checkList, DataList* typeCompat, DataList* result);
void startTypeCompatList(DataList* typeCompat);

void initializeObjList(DataList* typeCompat, DataList* xBased, DataList* result) {
	Initialize(xBased);
	Initialize(result);
	Initialize(typeCompat);
}
void uninitializeObjList(DataList* typeCompat,DataList* xBased, DataList* result) {
	Terminate(typeCompat);
	Terminate(xBased);
	Terminate(result);
}
void startObjList(StageClass* stage, DataList* typeCompat, DataList* xBased, DataList* result) {
	for (int i = 0; i < stage->getObjNum(); i++) {
		setObjEdge(xBased, &stage->getObj()[i]);
		//オブジェクト全ての左端・右端それぞれをノードとしてリストに登録
	}
	startTypeCompatList(typeCompat);
}
void finishObjList(DataList* typeCompat, DataList* xBased, DataList* result) {
	Clear(typeCompat);
	Clear(xBased);
	Clear(result);
}

void updateObjList(DataList* typeCompat,DataList* xBased, DataList* result) {
	Clear(result);//毎フレーム、前のresultを(要らない＋次作るまでに消しとかなきゃいけないので)消去
	sortObjEdgeListByX(xBased);//x端リストにオブジェクトの移動を反映
	optimizeObjList_getResult(typeCompat, xBased, result);
}

//既に作った結果リストを全部funcで参照する
void checkResultList(DataList* result, void func(ObjStr* a, ObjStr* b)) {
	result->crnt = result->head;// リストの着目ノードをリセット
	while (Next(result))
		func(result->crnt->d._oC.mp_objL, result->crnt->d._oC.mp_objR);
}

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
}

//オブジェクトの端をx順リストに登録
void setObjEdge(DataList* xBased, ObjStr* p_obj) {
	float size = getObjectSizeLonger(p_obj);//半径と辺、どちらが当たり判定かはともかく長い方
	InsertRearEdges(xBased, p_obj, p_obj->m_image.width / 2.0f - size, p_obj->m_image.width / 2.0f + size);
}

//リストの中身を画面に表示
void printList(DataList* draw) {
	Print(draw);
}

//毎フレーム、xBasedとfunc(なんらかの処理)をもとにresultを作成
void optimizeObjList_getResult(DataList* typeCompat, DataList* xBased, DataList* result) {

	//compatとは？…タイプ関係。余裕があったらタイプ関係による効率化もしたい

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

//チェックリストとタイプ相性リストを見つつ、タイプ相性リストに登録された関数の結果をリザルトリストに記録
void checkCheckList(DataList* checkList, DataList* typeCompat, DataList* result) {
	DataNode *sub_crnt; checkList->crnt = checkList->head;
	while (Next(checkList)) {//リストがダミーのみだったり見終わったら脱出
		sub_crnt = checkList->crnt;
		while (Next(checkList)) {
			//カレント以前のノードは一つ大きいループで調べ終わっている筈なので比べるのはcrntの次からでよい
			if (SearchObjCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj) == NULL) {// まだ結果リストにないものだったら
				typeCompat->crnt = typeCompat->head;//タイプ表のカレントをリセット
				while (SearchNextTypeCompat(typeCompat, sub_crnt->d._oE.mp_obj->m_type, checkList->crnt->d._oE.mp_obj->m_type)
					!= NULL) {//毎回カレントから出発し、見つかったらカレントを動かす検索。ヘッダに辿り着いたらNULL
					InsertRearCon(result, sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj, 
						(*typeCompat->crnt->d._tC.mp_func)(sub_crnt->d._oE.mp_obj, checkList->crnt->d._oE.mp_obj));
						// チェックリストに登録されていた関数(*mp_func)で得た結果(bool)を登録
				}
			}
		}
		checkList->crnt = sub_crnt;//大きいwhileのカレントまで戻す
	}
}


void startTypeCompatList(DataList* typeCompat) {
	setTypeCompats(typeCompat, NO_TYPE, TYPE_MAX, NO_TYPE, TYPE_MAX, true, &checkHitObjRR);//全タイプ

	deleteTypeCompats(typeCompat, CHARA_BLACKHOLE, CHARA_BLACKHOLE, NO_TYPE, TYPE_MAX, true, &checkHitObjRR);//ブラックホールと全タイプ

	deleteTypeCompats(typeCompat, NO_TYPE, TYPE_MAX, CHARA_BLACKHOLE, CHARA_BLACKHOLE, true, &checkHitObjRR);//全タイプとブラックホール
	setTypeCompats(typeCompat, NO_TYPE, TYPE_MAX, CHARA_BLACKHOLE, CHARA_BLACKHOLE, true, &sendObject);//全タイプとブラックホール
}

