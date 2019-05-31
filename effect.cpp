#include "effect.h"
#include "textDX.h"
#include "Image.h"
#include "textureLoader.h"
//#include "time.h"

Image eImage[eTYPE_MAX];//画像、最初に作って終わりなので
#define SPLIT_NUM (10)//分割回数

#define TAIL_LENGTH (1)//軌跡１つのpixel数

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

// データのタイプの比較関数
int DataTypeCmp(const EffNode* x, const EffNode* y)
{
	return x->effD.m_type < y->effD.m_type ? -1 : x->effD.m_type > y->effD.m_type ? 1 : 0;
}
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

/*// データの表示
void PrintData(const EffNode* n) {
	txtLineReset(int((n->effD.m_pos.y + n->effD.m_pos.y) / 2.0f));

	switch (n->effD.m_type) {
	case :
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
}*/

// なにかの条件でxと一致している、カレント以後で最も近いノードを探索
EffNode* SearchNext_notCrnt(EffList *list, EffNode* n,int comp(const EffNode* x, const EffNode* y))
{
	EffNode* ptr = list->crnt->next;//一個ずれて開始
	while (list->crnt != ptr) {//一周してしまったら終了
		if (ptr != list->head)//ヘッダーはまたげる
			if (comp(ptr, n) == 0)
				break;
		ptr = ptr->next;
	}
	return ptr;// 探索成功した場合はそのノード、失敗した場合は元のカレントノード
};

// なにかの条件でxと一致している、カレント以前で最も近いノードを探索
EffNode* SearchPrev_notCrnt(EffList *list, EffNode* n, int comp(const EffNode* x, const EffNode* y))
{
	EffNode* ptr = list->crnt->prev;//一個ずれて開始
	while (list->crnt != ptr) {//一周してしまったら終了
		if (ptr != list->head)//ヘッダーはまたげる
			if (comp(ptr, n) == 0)
				break;
		ptr = ptr->prev;
	}
	return ptr;// 探索成功した場合はそのノード、失敗した場合は元のカレントノード
};


// nとノードのポインタが一致しているノードを探索
EffNode* SearchNode(EffList *list, EffNode* n)
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

/*// 全ノードのデータをリスト順に表示
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
};*/

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
	Clear(list);			// 全ノードを削除
	free(list->head);		// ダミーノードを削除
};

//↑ローカル関数

void initializeEffect(EffList* eff) {
//	srand((unsigned)time(NULL));//randomize

	Initialize(eff);

	InitImage(&eImage[ePARTICLE], getTexture(textureLoaderNS::BIG_STAR), 0.0f,0.0f, 20, 20);
	InitImage(&eImage[eMAGIC], getTexture(textureLoaderNS::MAGIC_CIRCLE), 0.0f,0.0f, 100, 100);
//	eSPLITは砕く側から画像を貰うので空
	InitImage(&eImage[eTAIL], getTexture(textureLoaderNS::FIRE), 0.0f, 0.0f, TAIL_LENGTH, 39);

}
void uninitializeEffect(EffList* eff) {
	Terminate(eff);
}
void startEffect(EffList* eff) {};
void finishEffect(EffList* eff) {
	Clear(eff);
}
void updateEffect(EffList* eff) {
	eff->crnt = eff->head;// リストの着目ノードをリセット
	while (Next(eff)) {
		EffData *d = &eff->crnt->effD;
		d->m_time--;
		switch (d->m_type) {
		case ePARTICLE: {
			d->m_rot += 0.008f + 0.116f * float(d->m_time) / float(d->m_tMAX);
			EffData *c2 = &SearchPrev_notCrnt(eff, eff->crnt, DataTypeCmp)->effD//リスト内で前方にある同タイプのエフェクト
				, *c3 = &SearchNext_notCrnt(eff, eff->crnt, DataTypeCmp)->effD;//リスト内で後方にある同タイプのエフェクト
			d->m_accel = ((c2->m_pos + c3->m_pos) / 2.0f - d->m_pos) / 1000.0f;
			d->m_speed += d->m_accel;
			d->m_pos += d->m_speed;
			break;
		}
		case eLUMINE:
			break;
		case eSPLIT:
			d->m_speed += d->m_accel;
			d->m_pos += d->m_speed;
			break;
		case eTAIL:
			break;
		case eMAGIC: {
			d->m_rot += 0.008f + 0.116f * float(d->m_time) / float(d->m_tMAX);
			float f = 35.0f * float(d->m_time - d->m_tMAX * 2 / 3) / float(d->m_tMAX);
			d->m_image.width += int(f);
			d->m_image.height += int(f);
			d->m_pos = { d->m_pos.x - f / 2.0f ,d->m_pos.y - f / 2.0f };
			break;
		}
		default:
			break;
		}
		if (d->m_time <= 0) RemoveCurrent(eff);//時間いっぱいになって削除
	}
}
void drawEffect(EffList* eff) {
	eff->crnt = eff->head;// リストの着目ノードをリセット
	while (Next(eff)) {
		EffData *d = &eff->crnt->effD;
		switch (d->m_type) {
		case ePARTICLE:
			setPosition(&d->m_image, d->m_pos.x, d->m_pos.y);//サイズの更新も兼ねている
			setAngleRad(&d->m_image, d->m_rot);
			SetColorImage(&d->m_image, { 1.0f,1.0f,0.5f + 0.5f * float(d->m_time) / float(d->m_tMAX),
				1.5f * float(d->m_time) / float(d->m_tMAX) - 0.25f });//薄く黄色くなっていく
			break;
		case eLUMINE:
			break;
		case eSPLIT:
			movePosition(&d->m_image, d->m_pos.x, d->m_pos.y);//四点の関係は保持して移動だけ行う
			SetColorImage(&d->m_image, { 0.6f * float(d->m_time) / float(d->m_tMAX),0.6f * float(d->m_time) / float(d->m_tMAX),0.5f,
				3.0f * float(d->m_time) / float(d->m_tMAX)});//青くなっていき最後に一気に消える
			break;
		case eTAIL:
			setPosition(&d->m_image, d->m_pos.x, d->m_pos.y);//サイズの更新も兼ねている
			setAngleRad(&d->m_image, d->m_rot);
			SetColorImage(&d->m_image, { 1.0f,1.0f,1.0f,float(d->m_time) / float(d->m_tMAX)});//薄くなっていく
			break;
		case eMAGIC:
			setPosition(&d->m_image, d->m_pos.x, d->m_pos.y);//サイズの更新も兼ねている
			setAngleRad(&d->m_image, d->m_rot);
			SetColorImage(&d->m_image, { 1.0f,1.0f,1.0f,1.4f * float(d->m_time) / float(d->m_tMAX) - 0.1f });//薄くなっていく
			break;
		default:
			break;
		}
		DrawImage(&d->m_image);
	}
}


void makeParticle(EffList* eff, D3DXVECTOR2 pos) {
	float r; D3DXVECTOR2 speed;
	pos = { pos.x - eImage[ePARTICLE].width / 2,pos.y - eImage[ePARTICLE].height / 2 };
	for (int i = 0; i < 5; i++) {//5個作る
		r = float(rand() % 100) * D3DX_PI / 50.0f;
		speed = { 5.0f * cosf(r), 5.0f * sinf(r) };
		InsertRear(eff, { ePARTICLE, true, pos,
			r, { 1.0f, 1.0f}, speed, { 0.0f, 0.0f }, 100, 100, 0, eImage[ePARTICLE] });

		pos += {float(rand() % 31 - 15), float(rand() % 31 - 15)};
	}
}

void makeMagic(EffList* eff, D3DXVECTOR2 pos) {
	float r;
	r = float(rand() % 100) * D3DX_PI / 50.0f;
	InsertRear(eff, { eMAGIC, true, {pos.x - eImage[eMAGIC].width / 2 ,pos.y - eImage[eMAGIC].height / 2},
		r, { 1.0f, 1.0f}, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 40, 40, 0, eImage[eMAGIC] });
}

float randSplit() {
	return float(18 - rand() % 6) / 20.0f;
}//ローカル関数

void splitSquare(D3DXVECTOR2 pos2[4], D3DXVECTOR2 posed[4], int n0, int n1, int n2, int n3) {
	pos2[n0] = posed[n0] + (posed[n1] - posed[n0]) * randSplit();//古い方を割る
	pos2[n2] = posed[n2] + (posed[n3] - posed[n2]) * randSplit();//古い方を割る
	if (rand() % 3 != 0) {
		if (rand() % 2 == 0)
			pos2[n0] = posed[n1];
		else pos2[n2] = posed[n3];
	}
	pos2[n1] = posed[n1]; pos2[n3] = posed[n3];//古い方からもらう
	posed[n1] = pos2[n0]; posed[n3] = pos2[n2];//新しい方をもらう
}//ローカル関数

void makeSplit(EffList* eff, D3DXVECTOR2 pos, Image image) {
	Image img; D3DXVECTOR2 pos2[4]; D3DXVECTOR2 posed[4]; D3DXVECTOR2 speed; D3DXVECTOR2 accel;
	for (int i = 0; i < 4; i++)
		posed[i] = { 1.0f * float(i % 2),1.0f * float(i / 2) };//初期状態をZ字にセット

	for (int i = 0; i < SPLIT_NUM; i++) {//8個作る

		if (i != SPLIT_NUM - 1)
			switch(rand() % 4){
			case 0: splitSquare(pos2, posed, 0, 1, 2, 3); break;
			case 1: splitSquare(pos2, posed, 0, 2, 1, 3); break;
			case 2: splitSquare(pos2, posed, 3, 1, 2, 0); break;
			case 3: splitSquare(pos2, posed, 3, 2, 1, 0); break;
			}
		else
			for (int j = 0; j < 4; j++)
				pos2[j] = posed[j];

		InitImage(&img, &image.g_pD3DTexture, 0.0f, 0.0f, image.width, image.height);
		SetTexture(&img, pos2[0], pos2[1], pos2[2], pos2[3]);//テクスチャ頂点座標の変更

		for (int j = 0; j < 4; j++) {
			pos2[j].x *= image.width; pos2[j].y *= image.height;
			pos2[j] += pos;
		}
		setVertex(&img, pos2[0], pos2[1], pos2[2], pos2[3]);//描画頂点座標の変更

		speed = (pos2[0] + pos2[1] + pos2[2] + pos2[3]) / 4.0f//四点の中心
			- (pos + D3DXVECTOR2{ image.width / 2.0f,image.height / 2.0f });//図形の中心を引く
		speed /= 20.0f;//20で割る
		accel = { cosf(atan2f(speed.y,speed.x) + D3DX_PI / 2.0f),sinf(atan2f(speed.y,speed.x) + D3DX_PI / 2.0f) };
		accel *= sqrtf(speed.x * speed.x + speed.y * speed.y) / 45.0f;
		InsertRear(eff, { eSPLIT, true, pos2[0] - D3DXVECTOR2{ image.width / 2.0f,image.height / 2.0f },
			0.0f,{ 1.0f, 1.0f}, speed, accel, 40, 40, 0, img });
	}
}

void makeTail(EffList* eff, D3DXVECTOR2 pos, D3DXVECTOR2 speed) {
	float r; int num = 0;
	if (speed.x >= 0.0f) num += int(speed.x); else num -= int(speed.x);
	if (speed.y >= 0.0f) num += int(speed.y); else num -= int(speed.y);

	num = num / TAIL_LENGTH + 1;
	r = atan2f(speed.y, speed.x);
	pos -= speed;
	pos = { pos.x - eImage[eTAIL].width / 2, pos.y - eImage[eTAIL].height / 2 };

	for (int i = 0; i < num; i++) {
		pos += speed * float(1) / float(num);
		InsertRear(eff, { eTAIL, true, pos,
			r, { 1.0f, 1.0f}, {0.0f, 0.0f}, { 0.0f, 0.0f }, 60, 60, 0, eImage[eTAIL] });
	}
}

void makeEffect(EffList* eff, effTypes eType, ObjStr* obj) {
	switch (eType) {
	case ePARTICLE:
		makeParticle(eff, obj->m_pos);
		break;
	case eMAGIC:
		makeMagic(eff, obj->m_pos);
		break;
	case eSPLIT:
		makeSplit(eff, obj->m_pos, obj->m_image);
		break;
	case eTAIL:
		makeTail(eff, { obj->m_pos.x + obj->m_image.width / 2.0f,
			obj->m_pos.y + obj->m_image.height / 2.0f }, obj->m_speed + obj->m_accel);
		break;
	}
}

void setParticle(ObjStr* x, ObjStr* y) {

}