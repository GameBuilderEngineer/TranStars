#include "dataList.h"
#include "textDX.h"

// 一つのノードを動的に生成
static DataNode* AllocDnode(void)
{
	return (DataNode*)calloc(1, sizeof(DataNode));
}

// ノードの各メンバに値を設定
static void SetDnode(DataNode* n, const UnionData x, DataNode* prev, DataNode* next)
{
	n->d = x;
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}

// データ型ごとのデータをセット
static UnionData SetDataObjectEdge(ObjStr *p_obj, float dst, __data_objEdge *p_L) {
	UnionData d;
	d._oE.dType = DATA_OBJ_EDGE;
	d._oE.mp_obj = p_obj; d._oE.m_dst = dst; d._oE.mp_L = p_L;
	return d;
}
static UnionData SetDataObjectCon(ObjStr *p_objL, ObjStr *p_objR, bool use) {
	UnionData d;
	d._oC.dType = DATA_OBJ_CON;
	d._oC.mp_objL = p_objL; d._oC.mp_objR = p_objR; d._oC.m_use = use;
	return d;
}
static UnionData SetDataTypeCompat(objTypes type1, objTypes type2, bool use, bool(*p_func)(ObjStr* a, ObjStr* b)) {
	UnionData d;
	d._tC.dType = DATA_TYPE_COMPAT;
	d._tC.m_type1 = type1; d._tC.m_type2 = type2;
	d._tC.m_use = use;
	d._tC.mp_func = p_func;
	return d;
}

// リストは空か
static int IsEmpty(const DataList* list)
{
	return list->head->next == list->head;
}

// pが指すノードを削除
void Remove(DataList* list, DataNode* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// 削除したノードの先行ノードに着目
	free(p);
//	if (list->crnt == list->head)
//		list->crnt = list->head->next;
};

//a->b=(*a).b
//DataList->DataNode

// 着目ノードと着目の次ノードを、x座標について比べる
static int compareObjEdgeCurrentNextByX(DataList* list) {
	if (list->crnt == list->head || list->crnt->next == list->head)
		return -1;// どちらかがダミーノードで比べられない、という時は-1
	if (list->crnt->d._oE.mp_obj->m_pos.x + list->crnt->d._oE.m_dst <=
		list->crnt->next->d._oE.mp_obj->m_pos.x + list->crnt->next->d._oE.m_dst) return 1;//x昇順になっていれば
	return 0;//NOT x昇順ならば
}

// ノード1とノード2を、x座標について比べる
static int compareObjEdgeByX(const DataList* list, const DataNode* n1, const DataNode* n2) {
	if (n1 == list->head || n2 == list->head)
		return -1;// どちらかがダミーノードで比べられない、という時は-1
	if (n1->d._oE.mp_obj->m_pos.x + n1->d._oE.m_dst <=
		n2->d._oE.mp_obj->m_pos.x + n2->d._oE.m_dst) return 1;//x昇順になっていれば
	return 0;//NOT x昇順ならば
}


// データ1とデータ2を、タイプについて比べる
static int typeCompatCmp(const objTypes x, const objTypes y) {
	return x < y ? -1 : x > y ? 1 : 0;	//2つのデータが同じタイプの組み合わせを持つものであれば
}
// タイプが特殊なタイプであれば検出(true)する
static bool detectNoType(const objTypes t) {
	if (int(t) < int(NO_TYPE) || t == NO_TYPE || t == TYPE_MAX || int(TYPE_MAX) < int(t)) return true;
	return false;
}
//　タイプの大小をtype1が小さくなるように揃える
void sortTypeCompat(objTypes* t1,objTypes* t2) {
	if (int(*t1) > int(*t2)) {
		objTypes s = *t1;
		*t1 = *t2; *t2 = s;
	}
}

// データ型ごとのデータを比較
static int dataObjectEdgeCmp(const D_objEdge* d1 , const D_objEdge* d2) {
	return d1->dType != d2->dType ? 1 : d1->mp_obj != d2->mp_obj ? 1 : d1->m_dst != d2->m_dst ? 1 : d1->mp_L != d2->mp_L ? 1
		: 0;
};
static int dataObjectConCmp(const D_objCon* d1, const D_objCon* d2) {
	return d1->dType != d2->dType ? 1 : d1->mp_objL != d2->mp_objL ? 1 : d1->mp_objR != d2->mp_objR ? 1 : d1->m_use != d2->m_use ? 1
		: 0;
};
static int dataTypeCompatCmp(const D_typeCmp* d1, const D_typeCmp* d2) {
	return d1->dType != d2->dType ? 1 : d1->m_type1 != d2->m_type1 ? 1 : d1->m_type2 != d2->m_type2 ? 1 : d1->m_use != d2->m_use ? 1 : d1->mp_func != d2->mp_func ? 1
		: 0;
};
static int dataCmp(const UnionData* d1, const UnionData* d2) {
	if (d1->_oE.dType == DATA_OBJ_EDGE) return dataObjectEdgeCmp(&d1->_oE, &d2->_oE);
	if (d1->_oC.dType == DATA_OBJ_CON) return dataObjectConCmp(&d1->_oC, &d2->_oC);
	if (d1->_tC.dType == DATA_TYPE_COMPAT) return dataTypeCompatCmp(&d1->_tC, &d2->_tC);
	return 1;
};


// データのポインタの比較関数
int ObjPntrCmp(const ObjStr* x, const ObjStr* y)
{
	// xのポインタがyのポインタより小さい時→-1を戻す
	// xのポインタがyのポインタより大きい時→1を戻す
	// xのポインタとyのポインタが等しい時→0を戻す
	return x < y ? -1 : x > y ? 1 : 0;
};
// ノードのポインタの比較関数
int NodeCmp(const DataNode* x, const DataNode* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};
// データ型の確認関数
int DataTypeCmp(const UnionData* x, const UnionData* y)
{
	return x->_oE.dType < y->_oE.dType ? -1 : x->_oE.dType > y->_oE.dType ? 1 : 0;
};
// リストの確認関数
int DataListCmp(const DataList* x, const DataList* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};

//↑ローカル関数

// リストを初期化
void Initialize(DataList* list)
{
	DataNode* dummyNode = AllocDnode(); // ダミーノードを生成
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// 着目ノードのデータを表示
void PrintCurrent(const DataList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "着目ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		PrintData(list->crnt);
	}
}

// 関数compareによってxとデータ内容が一致しているノードを探索
DataNode* SearchObjEdge(DataList *list, const ObjStr* x)
{
	DataNode* ptr = list->head->next;
	if (ptr->d._oE.dType != DATA_OBJ_EDGE) return NULL;//データ型が違ったら失敗
	while (ptr != list->head)
	{
		if (ObjPntrCmp(ptr->d._oE.mp_obj, x) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};
DataNode* SearchObjCon(DataList *list, const ObjStr* x1, const ObjStr* x2)
{
	DataNode* ptr = list->head->next;
	if (ptr->d._oC.dType != DATA_OBJ_CON) return NULL;//データ型が違ったら失敗
	while (ptr != list->head)
	{
		if (ObjPntrCmp(ptr->d._oC.mp_objL, x1) == 0 && ObjPntrCmp(ptr->d._oC.mp_objR, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};
DataNode* SearchNextTypeCompat(DataList *list, const objTypes x1, const objTypes x2)
{
	DataNode* ptr = list->crnt->next;//カレントの次から出発
	if (ptr->d._tC.dType != DATA_TYPE_COMPAT) return NULL;//データ型が違ったら失敗
	while (ptr != list->head)
	{
		if (typeCompatCmp(ptr->d._tC.m_type1,x1) == 0 && typeCompatCmp(ptr->d._tC.m_type2, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// 探索成功
		}
		ptr = ptr->next;
	}
	return NULL;				// 探索失敗
};
DataNode* SearchNode(DataList *list, DataNode* n)
{
	DataNode* ptr = list->head->next;
	if (DataTypeCmp(&ptr->d, &n->d) != 0) return NULL;//データ型が違ったら失敗
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
DataNode* SearchData(DataList *list, UnionData* d)
{
	DataNode* ptr = list->head->next;
	if (DataTypeCmp(&ptr->d, d) != 0) return NULL;//データ型が違ったら失敗
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

// 全ノードのデータをリスト順に表示
void Print(const DataList* list)
{
	txtColorChange(getDebugFont(), 191, 95, 191, 63);//色変更
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		DataNode* ptr = list->head->next;
		printTextDX(getDebugFont(), "【一覧表】", WINDOW_CENTER_X, WINDOW_CENTER_Y,int(sizeof(UnionData)));//データサイズ
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->next;		// 後続ノードに着目
		}
	}
	txtColorChange(getDebugFont(), 255, 255, 255, 255);//色変更
};

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const DataList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		DataNode* ptr = list->head->prev;
		printTextDX(getDebugFont(), "【一覧表】", WINDOW_CENTER_X, WINDOW_CENTER_Y);
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};

// データの表示
void PrintData(const DataNode* n) {
	switch (n->d._oE.dType) {
	case DATA_OBJ_EDGE:
		PrintObjEdge(n);
		break;
	case DATA_OBJ_CON:
		PrintObjCon(n);
		break;
	case DATA_TYPE_COMPAT:
		PrintTypeCompat(n);
		break;
	default://存在しない型
		printTextDX(getDebugFont(), "？", WINDOW_CENTER_X, txtLineReset(txtLineReset(0)));
		break;
	}
}
void PrintObjEdge(const DataNode* n)
{
	int x = int(n->d._oE.mp_obj->m_pos.x + n->d._oE.m_dst);
	txtLineReset(int(n->d._oE.mp_obj->m_pos.y));

	printTextDX(getDebugFont(), "id：", x, txtLineBreak(), int(n->d._oE.mp_obj->m_id));
	printTextDX(getDebugFont(), "type：", x, txtLineBreak(), int(n->d._oE.mp_obj->m_type));
	printTextDX(getDebugFont(), "distance：", x, txtLineBreak(), int(n->d._oE.m_dst));
	if (n->d._oE.mp_L == NULL) printTextDX(getDebugFont(), "左端", x, txtLineBreak());
	else printTextDX(getDebugFont(), "右端", x, txtLineBreak());
};
void PrintObjCon(const DataNode* n)
{
	int x = int((n->d._oC.mp_objL->m_pos.x + n->d._oC.mp_objR->m_pos.x) / 2.0f);
	txtLineReset(int((n->d._oC.mp_objL->m_pos.y + n->d._oC.mp_objR->m_pos.y) / 2.0f));

	printTextDX(getDebugFont(), "左id：", x, txtLineBreak(), int(n->d._oC.mp_objL->m_id));
	printTextDX(getDebugFont(), "左type：", x, txtLineBreak(), int(n->d._oC.mp_objL->m_type));
	printTextDX(getDebugFont(), "右id：", x, txtLineBreak(), int(n->d._oC.mp_objR->m_id));
	printTextDX(getDebugFont(), "右type：", x, txtLineBreak(), int(n->d._oC.mp_objR->m_type));
	if (n->d._oC.m_use) printTextDX(getDebugFont(), "接触", x, txtLineBreak());
	else printTextDX(getDebugFont(), "非接触", x, txtLineBreak());
};
void PrintTypeCompat(const DataNode* n)
{
	txtLineReset(txtLineReset(0));

	printTextDX(getDebugFont(), "主type：", 0, txtLineBreak(), int(n->d._tC.m_type1));
	printTextDX(getDebugFont(), "受type：", 0, txtLineBreak(), int(n->d._tC.m_type2));
	if (n->d._tC.m_use == true) printTextDX(getDebugFont(), "有効", 0, txtLineBreak());
	else printTextDX(getDebugFont(), "無効", 0, txtLineBreak());
};

// 着目ノードを一つ後方に進める
int Next(DataList* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// 進めることはできない
	list->crnt = list->crnt->next;
	return 1;
};

// 着目ノードを一つ前方に戻す
int Prev(DataList* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// 戻すことはできない
	list->crnt = list->crnt->prev;
	return 1;
};

// pが指すノードの直後にノードを挿入
void InsertAfter(DataList* list, DataNode* p, const UnionData x)
{
	DataNode* ptr = AllocDnode();
	DataNode* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// 先頭にノードを挿入
void InsertFront(DataList* list, const UnionData x)
{
	InsertAfter(list, list->head, x);
};

// 末尾にノードを挿入
void InsertRear(DataList* list, const UnionData x)
{
	InsertAfter(list, list->head->prev, x);
};

// 末尾にオブジェクトの両端を挿入し、距離を設定
void InsertRearEdges(DataList* list, const ObjStr* x, float eL, float eR)
{
	InsertAfter(list, list->head->prev,
		SetDataObjectEdge((ObjStr*)x, eL, NULL));// 左端である

	__data_objEdge* p_L = &list->crnt->d._oE;//左端
	InsertAfter(list, list->head->prev,
		SetDataObjectEdge((ObjStr*)x, eR, p_L));// 右端であり、対応する左端のデータはp_Lである
};

// 末尾に２つのオブジェクトを辿れるノード、結果を挿入
void InsertRearCon(DataList* list, const ObjStr* x1, const ObjStr* x2, bool use)
{
	InsertAfter(list, list->head->prev,
		SetDataObjectCon((ObjStr*)x1, (ObjStr*)x2, use));
};

// 先頭ノードを削除
void RemoveFront(DataList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// 末尾ノードを削除
void RemoveRear(DataList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// 着目ノードを削除
void RemoveCurrent(DataList* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// 全ノードを削除
void Clear(DataList* list)
{
	while (!IsEmpty(list))	// 空になるまで
		RemoveFront(list);	// 先頭ノードを削除
};

// ノード1をノード2の直前に移動
void MoveDnodeBefore(DataNode* p_is, DataNode* p_to) {
	MoveDnodeAfter(p_to->prev, p_is);
};

// ノード2をノード1の直後に移動
void MoveDnodeAfter(DataNode* p_to, DataNode* p_is) {
	if (p_is != p_to) {
		//(どちらもダミーノードではないものとする)

		//p_isの前後にp_isを忘れさせる
		p_is->prev->next = p_is->next;
		p_is->next->prev = p_is->prev;

		//p_isに新しい前後ノードを覚えさせる
		p_is->prev = p_to;
		p_is->next = p_to->next;

		//p_toと次のノードにp_isを覚えさせる
		p_to->next->prev = p_is;
		p_to->next = p_is;
	}
};

// 循環・重連結リストの後始末
void Terminate(DataList* list)
{
	if (list->head != NULL) {
		Clear(list);			// 全ノードを削除
		free(list->head);		// ダミーノードを削除
	}
};


// オブジェクト端リストをx昇順に並び替え
void sortObjEdgeListByX(DataList* list) {
	list->crnt = list->head;//着目ノードをリセット
	while (Next(list)) {//最後までx座標順になったら0になって終了
		if (compareObjEdgeCurrentNextByX(list) == 0) {
			// (先頭ノード以外で)次ノードとの間でx座標順になっていないものを見つけていたら

			if (compareObjEdgeByX(list, list->crnt->prev, list->crnt->next) != 0) {
				//-1(head) , 0(>) , 1(<)
				//(1) カレントの前とカレントの次が順序立っていれば==おかしいのがカレントノードならば、カレント自身を右方向へ
				//(-1) カレントの前が先頭ノードなので比較できなかった場合も、カレント自身を右方向へ(左方向移動にくっ付けてもよいが、右方向の整列を兼ねられる可能性が高いのと、左方向移動の方でやるとPrevの初回抜けを回避しなければいけないため

				DataNode *crnt_prev = list->crnt->prev, *crnt_ = list->crnt;
				while (Next(list)) {
					if (compareObjEdgeByX(list, crnt_, list->crnt->next) != 0) {
						MoveDnodeBefore(crnt_, list->crnt->next);//カレントを、それらしいノードの前に移動
							//crnt->nextなのは、crnt_->next < crnt_なのは確定しているのと、while(Next(list))はcrntがhead(末尾)に到達した時点で抜けてしまうため
						break;
					}
				}
				list->crnt = crnt_prev;//この後Nextされる
			}
			else{// でなければ
				//-1(head) , 0(>) , 1(<)
				//(0) おかしいのがカレントの次ノードならば、カレントの次を左方向へ移動
				DataNode *crnt_prev = list->crnt->prev, *crnt_next = list->crnt->next;
				while (Prev(list)) {
					if (compareObjEdgeByX(list, list->crnt->prev, crnt_next) != 0) {
						MoveDnodeAfter(list->crnt->prev, crnt_next);//カレントの次を、それらしいノードの次に移動
							//crnt->prevなのは、crnt_next < crnt_->prevなのは確定しているのと、while(Prev(list))はcrntがhead(先頭)に到達した時点で抜けてしまうため
						break;
					}
				}
//				list->crnt = crnt_;//この後Nextされる crnt_nextが移動した後の(crnt_ < crnt_->Next)が保証されないのでダメ
				list->crnt = crnt_prev;//この後Nextされる
			}
		}
	}
}
//ifやwhileなどの条件式内で関数を呼んだ場合にも値は書き変わる。

// 2つのタイプ、useフラグの初期状態、用いる関数を登録
void setTypeCompat(DataList* list, objTypes type1, objTypes type2, bool use, bool (*p_func)(ObjStr* a, ObjStr* b)){
	if (!detectNoType(type1) && !detectNoType(type2))//NoTypeならtrue
		InsertRear(list, SetDataTypeCompat(type1, type2, use, p_func));
}

// 複数対複数(type1L<=type1<=type1Hとtype2L<=type2<=type2H)のタイプ関係群と、useフラグの初期状態、用いる関数を登録
void setTypeCompats(DataList* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H
	, bool use, bool(*p_func)(ObjStr* a, ObjStr* b)) {
	//setTypeCompatが個別に除外するので、両端にはNO_TYPEとかを入れても構わない
	for (int i = int(type1L); i <= int(type1H); i++)
		for (int j = int(type2L); j <= int(type2H); j++) {
			UnionData d = SetDataTypeCompat((objTypes)i, (objTypes)j, use, p_func);
			if (SearchData(list, &d) == NULL)//同じ処理はまだなかったら
				setTypeCompat(list, (objTypes)i, (objTypes)j, use, p_func);
		}
}

void deleteTypeCompat(DataList* list, objTypes type1, objTypes type2, bool use, bool(*p_func)(ObjStr* a, ObjStr* b)) {
	UnionData d = SetDataTypeCompat(type1, type2, use, p_func);
	if (!detectNoType(type1) && !detectNoType(type2))//NoTypeならtrue
		if (SearchData(list, &d) != NULL)//同じ処理があったら
			Remove(list, list->crnt);
}

void deleteTypeCompats(DataList* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H
	, bool use, bool(*p_func)(ObjStr* a, ObjStr* b)) {
	//setTypeCompatが個別に除外するので、両端にはNO_TYPEとかを入れても構わない
	for (int i = int(type1L); i <= int(type1H); i++)
		for (int j = int(type2L); j <= int(type2H); j++)
			deleteTypeCompat(list, (objTypes)i, (objTypes)j, use, p_func);
}