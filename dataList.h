#pragma once
// 循環・重連結リスト(ヘッダ部)

#include "object.h"

enum dataTypes {
	DATA_NO_TYPE = -1,
	DATA_OBJ_EDGE,
	DATA_OBJ_CON,
};

// データ型(0)(ダミーノード用)
typedef struct __data_noType {
	dataTypes dType;					// データのタイプ
}D_noType;

// データ型①(オブジェクト端のx座標)
typedef struct __data_objEdge {
	dataTypes dType;					// データのタイプ

	ObjStr *mp_obj;						// データ
	float m_dst;						// オブジェクトの座標からその端までの距離
	struct __data_objEdge *mp_L;		// オブジェクトの左端を覚えたデータへのポインタ(自分が左端だった場合はNULL)
}D_objEdge;

// データ型②(処理を通した結果返ってきた、オブジェクト同士の関係)
typedef struct {
	dataTypes dType;					// データのタイプ

	ObjStr *mp_objL;					// データ1(左にいるオブジェクト)
	ObjStr *mp_objR;					// データ2(右にいるオブジェクト)
	bool m_use;							// そのオブジェクト関係の判定結果がどうだったか
}D_objCon;
// 統一データ型
typedef union {
	D_noType _nT;
	D_objEdge _oE;
	D_objCon _oC;
}UnionData;

// ノード
typedef struct __node_obj {
	UnionData d;
	struct __node_obj *prev;			// 前ノードへのポインタ
	struct __node_obj *next;			// 後ノードへのポインタ
}DataNode;

// 循環・重連結リスト
typedef struct {
	DataNode *head;						// 先頭(左端)ダミーノードへのポインタ
	DataNode *crnt;						// 着目ノードへのポインタ
}DataList;


// リストを初期化
void Initialize(DataList *list);

// 着目ノードのデータを表示
void PrintCurrent(const DataList *list);

// 関数compareによって(x)/(x1,x2)とデータ内容が一致しているノードを探索
DataNode* SearchObjEdge(DataList *list, const ObjStr* x);
DataNode* SearchNextObjEdge(DataList *list, const ObjStr* x);
DataNode* SearchObjCon(DataList *list, const ObjStr* x1, const ObjStr* x2);
DataNode* SearchNode(DataList *list, DataNode* n);
DataNode* SearchData(DataList *list, UnionData* d);

// 全ノードのデータをリスト順に表示
void Print(const DataList* list);

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const DataList* list);

// データの表示（改行なし）
void PrintData(const DataNode* n);
void PrintObjEdge(const DataNode* n);
void PrintObjCon(const DataNode* n);

// 着目ノードを一つ後方に進める
int Next(DataList* list);

// 着目ノードを一つ前方に戻す
int Prev(DataList* list);

// pが指すノードの直後にノードを挿入
void InsertAfter(DataList* list, DataNode* p, const UnionData x);

// 先頭にノードを挿入
void InsertFront(DataList* list, const UnionData x);

// 末尾にノードを挿入
void InsertRear(DataList* list, const UnionData x);

// 末尾にオブジェクトの両端を挿入し、距離を設定
void InsertRearEdges(DataList* list, const ObjStr* x, float eL, float eR);
// 末尾に２つのオブジェクトを辿れるノード、結果を挿入
void InsertRearCon(DataList* list, const ObjStr* x1, const ObjStr* x2, bool use);

// 先頭ノードを削除
void RemoveFront(DataList* list);

// 末尾ノードを削除
void RemoveRear(DataList* list);

// 着目ノードを削除
void RemoveCurrent(DataList* list);

// 全ノードを削除
void Clear(DataList* list);

// ノード1をノード2の直前に移動
void MoveDnodeBefore(DataNode* p_is, DataNode* p_to);
// ノード1をノード2の直後に移動
void MoveDnodeAfter(DataNode* p_is, DataNode* p_to);

// 循環・重連結リストの後始末
void Terminate(DataList* list);

// リストに登録されているオブジェクトの端を全てx順にソート
void sortObjEdgeListByX(DataList* list);
