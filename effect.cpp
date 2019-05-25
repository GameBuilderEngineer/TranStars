#include "effect.h"
#include "textDX.h"
#include "image.h"
#include "textureLoader.h"

// 一つのノードを動的に生成
static EffNode* AllocDnode(void)
{
	return (EffNode*)calloc(1, sizeof(EffNode));
}

// ノードの各メンバに値を設定
static void SetDnode(EffNode* n, const EffData x, EffNode* prev, EffNode* next)
{
	n->effD = x;
	n->prev = prev;		// 先行ノードへのポインタ
	n->next = next;		// 後続ノードへのポインタ
}

// リストは空か
static int IsEmpty(const EffList* list)
{
	return list->head->next == list->head;
}

// pが指すノードを削除
void Remove(EffList* list, EffNode* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// 削除したノードの先行ノードに着目
	free(p);
//	if (list->crnt == list->head)
//		list->crnt = list->head->next;
};

//a->b=(*a).b
//EffList->EffNode

// データのポインタの比較関数
int DataPntrCmp(const EffData* x, const EffData* y)
{
	// xのポインタがyのポインタより小さい時→-1を戻す
	// xのポインタがyのポインタより大きい時→1を戻す
	// xのポインタとyのポインタが等しい時→0を戻す
	return x < y ? -1 : x > y ? 1 : 0;
};
// ノードのポインタの比較関数
int NodeCmp(const EffNode* x, const EffNode* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};

// リストを初期化
void Initialize(EffList* list)
{
	EffNode* dummyNode = AllocDnode(); // ダミーノードを生成
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

// データの表示
void PrintData(const EffNode* n) {
	txtLineReset(int((n->effD.m_pos.y + n->effD.m_pos.y) / 2.0f));

	switch (n->effD.m_type) {
	case ePARTICLE:
//		PrintObjEdge(n);
		break;
	case eLUMINE:
//		PrintObjCon(n);
		break;
	case eSPLIT:
//		PrintTypeCompat(n);
		break;
	default://存在しない型
		printTextDX(getDebugFont(), "？", WINDOW_CENTER_X, txtLineReset(txtLineReset(0)));
		break;
	}
}

// 着目ノードのデータを表示
void PrintCurrent(const EffList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "着目ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		PrintData(list->crnt);
	}
}

// 関数compareによってxとデータ内容が一致しているノードを探索
EffNode* Search(EffList *list, EffNode* n)
{
	EffNode* ptr = list->head->next;
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

// 全ノードのデータをリスト順に表示
void Print(const EffList* list)
{
	txtColorChange(getDebugFont(), 191, 95, 191, 63);//色変更
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		EffNode* ptr = list->head->next;
		printTextDX(getDebugFont(), "【一覧表】", WINDOW_CENTER_X, WINDOW_CENTER_Y,
			int(sizeof(EffData)));
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->next;		// 後続ノードに着目
		}
	}
	txtColorChange(getDebugFont(), 255, 255, 255, 255);//色変更
};

// 全ノードのデータをリストの逆順に表示
void PrintReverse(const EffList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "ノードがありません。", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		EffNode* ptr = list->head->prev;
		printTextDX(getDebugFont(), "【一覧表】", WINDOW_CENTER_X, WINDOW_CENTER_Y);
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->prev;		// 先行ノードに着目
		}
	}
};

// 着目ノードを一つ後方に進める
int Next(EffList* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// 進めることはできない
	list->crnt = list->crnt->next;
	return 1;
};

// 着目ノードを一つ前方に戻す
int Prev(EffList* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// 戻すことはできない
	list->crnt = list->crnt->prev;
	return 1;
};

// pが指すノードの直後にノードを挿入
void InsertAfter(EffList* list, EffNode* p, const EffData x)
{
	EffNode* ptr = AllocDnode();
	EffNode* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// 先頭にノードを挿入
void InsertFront(EffList* list, const EffData x)
{
	InsertAfter(list, list->head, x);
};

// 末尾にノードを挿入
void InsertRear(EffList* list, const EffData x)
{
	InsertAfter(list, list->head->prev, x);
};

// 先頭ノードを削除
void RemoveFront(EffList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// 末尾ノードを削除
void RemoveRear(EffList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// 着目ノードを削除
void RemoveCurrent(EffList* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// 全ノードを削除
void Clear(EffList* list)
{
	while (!IsEmpty(list))	// 空になるまで
		RemoveFront(list);	// 先頭ノードを削除
};

// ノード2をノード1の直後に移動
void MoveDnodeAfter(EffNode* p_to, EffNode* p_is) {
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

// ノード1をノード2の直前に移動
void MoveDnodeBefore(EffNode* p_is, EffNode* p_to) {
	MoveDnodeAfter(p_to->prev, p_is);
};

// 循環・重連結リストの後始末
void Terminate(EffList* list)
{
	if (list->head != NULL) {
		Clear(list);			// 全ノードを削除
		free(list->head);		// ダミーノードを削除
	}
};

//↑ローカル関数

void initializeEffect(EffList* eff) {
	Initialize(eff);
}
void uninitializeEffect(EffList* eff) {
	Terminate(eff);
}
void updateEffect(EffList* eff) {
	eff->crnt = eff->head;// リストの着目ノードをリセット
	while (Next(eff)) {
		EffData *c = &eff->crnt->effD;
		c->m_time--;
		if (c->m_time <= 0) RemoveCurrent(eff);//時間いっぱいになって削除
		switch (c->m_type) {
		case ePARTICLE:
			c->m_rot += 0.5f + 7.0f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX);
			EffData *c2, *c3;
			if (eff->crnt->prev != eff->head) c2 = &eff->crnt->prev->effD;
			else c2 = &eff->head->prev->effD;
			if (eff->crnt->next != eff->head) c3 = &eff->crnt->next->effD;
			else c3 = &eff->head->next->effD;
			c->m_accel = ((c2->m_pos + c3->m_pos) / 2.0f - c->m_pos) / 1000.0f;
			c->m_speed += c->m_accel;
			c->m_pos += c->m_speed;

			break;
		case eLUMINE:
			break;
		case eSPLIT:
			break;
		default:
			break;
		}
	}
}
void drawEffect(EffList* eff) {
	eff->crnt = eff->head;// リストの着目ノードをリセット
	while (Next(eff)) {
		setPosition(&eff->crnt->effD.m_image, eff->crnt->effD.m_pos.x, eff->crnt->effD.m_pos.y);
		setAngle(&eff->crnt->effD.m_image, eff->crnt->effD.m_rot);
		SetColorImage(&eff->crnt->effD.m_image, { 1.0f,1.0f,0.5f + 0.5f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX),
			1.5f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX) -0.25f});//薄くなっていく
		DrawImage(&(eff->crnt->effD.m_image));
	}
}


void makeParticle(EffList* eff, D3DXVECTOR2 pos) {
	Image img; float c; D3DXVECTOR2 speed;
	for (int i = 0; i < 5; i++) {//5個作る
		c = float(rand() % 100);
		speed = { 5.0f * cosf(c), 5.0f * sinf(c) };

		InitAnimeImage(&img, getTexture(textureLoaderNS::STAR3), pos.x, pos.y, 20, 20, 3, 1, 1, 1);
		InsertRear(eff, { ePARTICLE, true, pos, 0.0f, { 1.0f, 1.0f}, speed, { 0.0f, 0.0f }, 100, 100, 0, img });

		pos += {float(rand() % 31 - 15), float(rand() % 31 - 15)};
	}
}

