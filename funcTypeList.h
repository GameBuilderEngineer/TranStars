#pragma once
// 循環・重連結リスト(ヘッダ部)

#include "object.h"
#include "effect.h"

enum funcTypes {
	FUNC_NO_TYPE = -1,
	FUNC_COLLISION,
	FUNC_ACTION,
	FUNC_ACTION_EFFECT
};

// 関数入れた共用体
typedef union {
	void (*_n);//FUNC_NO_TYPE
	bool (*_b)(ObjStr* a, ObjStr* b);//FUNC_COLLISION
	void (*_v)(ObjStr* a, ObjStr* b);//FUNC_ACTION
	void (*_ef)(ObjStr* a, ObjStr* b, EffList* eff);//FUNC_ACTION_EFFECT
}UnionFunc;

//データ
typedef struct {
	objTypes m_type1;					// オブジェクトタイプ1
	objTypes m_type2;					// オブジェクトタイプ2
	bool m_use;							// 下の関数で1から2に干渉するか

	funcTypes fType;					// 関数型
	UnionFunc mp_func;					// 使う関数
}TF_Data;

// ノード
typedef struct __node_tf {
	TF_Data d;
	struct __node_tf *prev;			// 前ノードへのポインタ
	struct __node_tf *next;			// 後ノードへのポインタ
}TF_Node;

// 循環・重連結リスト
typedef struct {
	TF_Node *head;						// 先頭(左端)ダミーノードへのポインタ
	TF_Node *crnt;						// 着目ノードへのポインタ
}TF_List;

// リストを初期化
void Initialize(TF_List *list);

// (x1,x2)と関係タイプが一致しているノードを探索
TF_Node* SearchNextTF_byObjType(TF_List *list, const objTypes x1, const objTypes x2);
// nとノードのポインタが一致しているノードを探索
TF_Node* SearchTF_Node(TF_List *list, TF_Node* n);
// dとデータの全メンバが一致しているノードを探索
TF_Node* SearchTF_Data(TF_List *list, TF_Data* d);

/*// 全ノードのデータをリスト順に表示
void Print(const TF_List* list);

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const TF_List* list);

// データの表示（改行なし）
void PrintData(const TF_Node* n);
void PrintTypeFunc(const TF_Node* n);*/

// 着目ノードを一つ後方に進める
int Next(TF_List* list);

// 着目ノードを一つ前方に戻す
int Prev(TF_List* list);

// pが指すノードの直後にノードを挿入
void InsertAfter(TF_List* list, TF_Node* p, const TF_Data x);

// 先頭にノードを挿入
void InsertFront(TF_List* list, const TF_Data x);

// 末尾にノードを挿入
void InsertRear(TF_List* list, const TF_Data x);

// 先頭ノードを削除
void RemoveFront(TF_List* list);

// 末尾ノードを削除
void RemoveRear(TF_List* list);

// 着目ノードを削除
void RemoveCurrent(TF_List* list);

// 全ノードを削除
void Clear(TF_List* list);

// 循環・重連結リストの後始末
void Terminate(TF_List* list);

// 2つのタイプ、useフラグの初期状態、用いる関数をリストに登録
void setTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func);
// 複数対複数(type1L<=type1<=type1Hとtype2L<=type2<=type2H)のタイプ関係群と、useフラグの初期状態、用いる関数をリストに登録
void setTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func);
// 条件に合うものをタイプリストから消す
void deleteTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func);//
// 条件に合うものをタイプリストから消す
void deleteTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func);

// タイプリストから、タイプが順序逆になってるだけなものを消す
void optimizeTypeFuncs(TF_List* list);

UnionFunc castFunc(static bool(*p_func)(ObjStr* a, ObjStr* b));
UnionFunc castFunc(static void(*p_func)(ObjStr* a, ObjStr* b));
UnionFunc castFunc(static void(*p_func)(ObjStr* a, ObjStr* b,EffList* eff));

