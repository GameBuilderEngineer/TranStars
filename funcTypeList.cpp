#include "funcTypeList.h"
#include "textDX.h"

// 一つのノードを動的に生成
static TF_Node* AllocDnode(void)
{
	return (TF_Node*)calloc(1, sizeof(TF_Node));
}

// ノードの各メンバに値を設定
static void SetDnode(TF_Node* n, const TF_Data x, TF_Node* prev, TF_Node* next)
{
	n->d = x;
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}

// 関数型ごとの関数をセット
void SetTF_NoType(TF_Data* d) {
	d->fType = FUNC_NO_TYPE;
}
void SetTF_Collision(TF_Data* d, static bool(*p_func)(ObjStr* a, ObjStr* b)) {
	d->fType = FUNC_COLLISION;
	d->mp_func._b = p_func;
}
void SetTF_Action(TF_Data* d, static void(*p_func)(ObjStr* a, ObjStr* b)) {
	d->fType = FUNC_ACTION;
	d->mp_func._v = p_func;
}
void SetTF_Action_Effect(TF_Data* d, static void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff)) {
	d->fType = FUNC_ACTION_EFFECT;
	d->mp_func._ef = p_func;
}
// データをセット
TF_Data SetTF_Data(objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func) {
	TF_Data d;
	d.m_type1 = type1; d.m_type2 = type2;
	d.m_use = use;

	switch (fType) {
	case FUNC_COLLISION:
		SetTF_Collision(&d, p_func._b);
		break;
	case FUNC_ACTION:
		SetTF_Action(&d, p_func._v);
		break;
	case FUNC_ACTION_EFFECT:
		SetTF_Action_Effect(&d, p_func._ef);
		break;
	default://存在しない型
		SetTF_NoType(&d);
		break;
	}
	return d;
}


// リストは空か
static int IsEmpty(const TF_List* list)
{
	return list->head->next == list->head;
}

// pが指すノードを削除
void Remove(TF_List* list, TF_Node* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// 削除したノードの先行ノードに着目
	free(p);
//	if (list->crnt == list->head)
//		list->crnt = list->head->next;
};

// タイプを比較する
static int typeCmp(const objTypes x, const objTypes y) {
	return x < y ? -1 : x > y ? 1 : 0;	//2つのデータが同じタイプの組み合わせを持つものであれば
}
// タイプが特殊なタイプであれば検出(true)する
static bool detectNoType(const objTypes t) {
	if (int(t) < int(NO_TYPE) || t == NO_TYPE || t == TYPE_MAX || int(TYPE_MAX) < int(t)) return true;
	return false;
}
//　タイプの大小をtype1が小さくなるように揃える
void sortType(objTypes* t1, objTypes* t2) {
	if (int(*t1) > int(*t2)) {
		objTypes s = *t1;
		*t1 = *t2; *t2 = s;
	}
}

// データ全体を比較
static int dataCmp(const TF_Data* d1, const TF_Data* d2) {
	return d1->m_type1 != d2->m_type1 ? 1 : d1->m_type2 != d2->m_type2 ? 1 : d1->m_use != d2->m_use ? 1 : d1->fType != d2->fType ? 1 : d1->mp_func._n != d2->mp_func._n ? 1
		: 0;//全部一緒なら0
};


// ノードのポインタの比較関数
int NodeCmp(const TF_Node* x, const TF_Node* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};
// 関数型の確認関数
int FuncTypeCmp(const TF_Data* x, const TF_Data* y)
{
	return x->fType < y->fType ? -1 : x->fType > y->fType ? 1 : 0;
};
// リストの確認関数
int TF_ListCmp(const TF_List* x, const TF_List* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};

//↑ローカル関数

// リストを初期化
void Initialize(TF_List* list)
{
	TF_Node* dummyNode = AllocDnode(); // ダミーノードを生成
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;

	SetTF_NoType(&dummyNode->d);
}

TF_Node* SearchNextTF_byObjType(TF_List *list, const objTypes x1, const objTypes x2)
{
	TF_Node* ptr = list->crnt->next;//カレントの次から出発
	while (ptr != list->head)
	{
		if (typeCmp(ptr->d.m_type1, x1) == 0 && typeCmp(ptr->d.m_type2, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};
TF_Node* SearchTF_Node(TF_List *list, TF_Node* n)
{
	TF_Node* ptr = list->head->next;
	if (FuncTypeCmp(&ptr->d, &n->d) != 0) return NULL;//データ型が違ったら失敗
	while (ptr != list->head)
	{
		if (NodeCmp(ptr, n) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};
TF_Node* SearchTF_Data(TF_List *list, TF_Data* d)
{
	TF_Node* ptr = list->head->next;
	if (FuncTypeCmp(&ptr->d, d) != 0) return NULL;//データ型が違ったら失敗
	while (ptr != list->head)
	{
		if (dataCmp(&ptr->d, d) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};

/*
// 全ノードのデータをリスト順に表示
void Print(const TF_List* list)
{
	txtColorChange(getDebugFont(), 191, 95, 191, 63);//色変更
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		TF_Node* ptr = list->head->next;
		printTextDX(getDebugFont(), "【一覧表】", WINDOW_CENTER_X, WINDOW_CENTER_Y, int(sizeof(NULL)));//データサイズ
		while (ptr != list->head) {
			PrintTF(ptr);
			ptr = ptr->next;		// 後続ノードに着目
		}
	}
	txtColorChange(getDebugFont(), 255, 255, 255, 255);//色変更
};

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const TF_List* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		TF_Node* ptr = list->head->prev;
		printTextDX(getDebugFont(), "【一覧表】", WINDOW_CENTER_X, WINDOW_CENTER_Y);
		while (ptr != list->head) {
			PrintTF(ptr);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};

// データの表示
void PrintTF(const TF_Node* n) {
	switch (n->d.fType) {
	case FUNC_COLLISION:
		PrintTF_Collision(n);
		break;
	case FUNC_ACTION:
		PrintTF_Action(n);
		break;
	case FUNC_ACTION_EFFECT:
		PrintTF_Action_Effect(n);
		break;
	default://存在しない型
		printTextDX(getDebugFont(), "？", WINDOW_CENTER_X, txtLineReset(txtLineReset(0)));
		break;
	}
}

void PrintTF_Collision(const TF_Node* n)
{
	txtLineReset(txtLineReset(0));

	printTextDX(getDebugFont(), "主type：", 0, txtLineBreak(), int(n->d.m_type1));
	printTextDX(getDebugFont(), "受type：", 0, txtLineBreak(), int(n->d.m_type2));
	if (n->d.m_use == true) printTextDX(getDebugFont(), "有効", 0, txtLineBreak());
	else printTextDX(getDebugFont(), "無効", 0, txtLineBreak());
};
*/

// 着目ノードを一つ後方に進める
int Next(TF_List* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// 進めることはできない
	list->crnt = list->crnt->next;
	return 1;
};

// 着目ノードを一つ前方に戻す
int Prev(TF_List* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// 戻すことはできない
	list->crnt = list->crnt->prev;
	return 1;
};

// pが指すノードの直後にノードを挿入
void InsertAfter(TF_List* list, TF_Node* p, const TF_Data x)
{
	TF_Node* ptr = AllocDnode();
	TF_Node* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// 先頭にノードを挿入
void InsertFront(TF_List* list, const TF_Data x)
{
	InsertAfter(list, list->head, x);
};

// 末尾にノードを挿入
void InsertRear(TF_List* list, const TF_Data x)
{
	InsertAfter(list, list->head->prev, x);
};

// 先頭ノードを削除
void RemoveFront(TF_List* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// 末尾ノードを削除
void RemoveRear(TF_List* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// 着目ノードを削除
void RemoveCurrent(TF_List* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// 全ノードを削除
void Clear(TF_List* list)
{
	while (!IsEmpty(list))	// 空になるまで
		RemoveFront(list);	// 先頭ノードを削除
};

// 循環・重連結リストの後始末
void Terminate(TF_List* list)
{
	if (list->head != NULL) {
		Clear(list);			// 全ノードを削除
		free(list->head);		// ダミーノードを削除
	}
};


// 2つのタイプ、useフラグの初期状態、用いる関数を登録
void setTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func) {
	if (!detectNoType(type1) && !detectNoType(type2)) {//NoTypeならtrue
		InsertRear(list, SetTF_Data(type1, type2, use, fType, p_func));
	}
}

// 複数対複数(type1L<=type1<=type1Hとtype2L<=type2<=type2H)のタイプ関係群と、useフラグの初期状態、用いる関数を登録
void setTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func) {
	//setTypeFuncが個別に除外するので、両端にはNO_TYPEとかを入れても構わない
	for (int i = int(type1L); i <= int(type1H); i++)
		for (int j = int(type2L); j <= int(type2H); j++) {
			TF_Data d = SetTF_Data(objTypes(i), objTypes(j), use, fType, p_func);
			if (SearchTF_Data(list, &d) == NULL)//同じ処理はまだなかったら
				setTypeFunc(list, objTypes(i), objTypes(j), use, fType, p_func);
		}
}

// 2つのタイプ、useフラグの初期状態、用いる関数を削除
void deleteTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func) {
	TF_Data d = SetTF_Data(type1, type2, use, fType, p_func);
	if (!detectNoType(type1) && !detectNoType(type2))//NoTypeならtrue
		if (SearchTF_Data(list, &d) != NULL)//同じ処理があったら、そこがカレントになるので
			Remove(list, list->crnt);
}

// 複数対複数(type1L<=type1<=type1Hとtype2L<=type2<=type2H)のタイプ関係群と、useフラグの初期状態、用いる関数を削除
void deleteTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func) {
	//deleteTypeFuncが個別に除外するので、両端にはNO_TYPEとかを入れても構わない
	for (int i = int(type1L); i <= int(type1H); i++)
		for (int j = int(type2L); j <= int(type2H); j++)
			deleteTypeFunc(list, objTypes(i), objTypes(j), use, fType, p_func);
}

//最適化
void optimizeTypeFuncs(TF_List* list) {
	TF_Node* n = list->head->next;
	for (int i = int(NO_TYPE) + 1; i <= int(TYPE_MAX) - 1; i++)
		for (int j = i + 1; j < int(TYPE_MAX); j++)
			while (n != NULL) {
				deleteTypeFunc(list, objTypes(i), objTypes(j), n->d.m_use,n->d.fType, n->d.mp_func);
				//タイプの組み合わせが逆で処理が一緒なものを探して削除
				n = SearchNextTF_byObjType(list, (objTypes)i, (objTypes)j);
			}
}

UnionFunc castFunc(static bool(*p_func)(ObjStr* a, ObjStr* b)) {
	UnionFunc f;
	f._b = p_func;
	return f;
}
UnionFunc castFunc(static void(*p_func)(ObjStr* a, ObjStr* b)) {
	UnionFunc f;
	f._v = p_func;
	return f;
}
UnionFunc castFunc(static void(*p_func)(ObjStr* a, ObjStr* b, EffList* eff)) {
	UnionFunc f;
	f._ef = p_func;
	return f;
}
