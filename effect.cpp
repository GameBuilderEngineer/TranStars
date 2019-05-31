#include "effect.h"
#include "textDX.h"
#include "Image.h"
#include "textureLoader.h"
//#include "time.h"

Image eImage[eTYPE_MAX];//�摜�A�ŏ��ɍ���ďI���Ȃ̂�
#define SPLIT_NUM (10)//������

#define TAIL_LENGTH (1)//�O�ՂP��pixel��

// ��̃m�[�h�𓮓I�ɐ���
static EffNode* AllocDnode(void)
{
	return (EffNode*)calloc(1, sizeof(EffNode));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode(EffNode* n, const EffData x, EffNode* prev, EffNode* next)
{
	n->effD = x;
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// ���X�g�͋�
static int IsEmpty(const EffList* list)
{
	return list->head->next == list->head;
}

// p���w���m�[�h���폜
void Remove(EffList* list, EffNode* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// �폜�����m�[�h�̐�s�m�[�h�ɒ���
	free(p);
//	if (list->crnt == list->head)
//		list->crnt = list->head->next;
};

//a->b=(*a).b
//EffList->EffNode

// �f�[�^�̃^�C�v�̔�r�֐�
int DataTypeCmp(const EffNode* x, const EffNode* y)
{
	return x->effD.m_type < y->effD.m_type ? -1 : x->effD.m_type > y->effD.m_type ? 1 : 0;
}
// �f�[�^�̃|�C���^�̔�r�֐�
int DataPntrCmp(const EffData* x, const EffData* y)
{
	// x�̃|�C���^��y�̃|�C���^��菬��������-1��߂�
	// x�̃|�C���^��y�̃|�C���^���傫������1��߂�
	// x�̃|�C���^��y�̃|�C���^������������0��߂�
	return x < y ? -1 : x > y ? 1 : 0;
};
// �m�[�h�̃|�C���^�̔�r�֐�
int NodeCmp(const EffNode* x, const EffNode* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};

// ���X�g��������
void Initialize(EffList* list)
{
	EffNode* dummyNode = AllocDnode(); // �_�~�[�m�[�h�𐶐�
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;
}

/*// �f�[�^�̕\��
void PrintData(const EffNode* n) {
	txtLineReset(int((n->effD.m_pos.y + n->effD.m_pos.y) / 2.0f));

	switch (n->effD.m_type) {
	case :
	default://���݂��Ȃ��^
		printTextDX(getDebugFont(), "�H", WINDOW_CENTER_X, txtLineReset(txtLineReset(0)));
		break;
	}
}

// ���ڃm�[�h�̃f�[�^��\��
void PrintCurrent(const EffList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "���ڃm�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		PrintData(list->crnt);
	}
}*/

// �Ȃɂ��̏�����x�ƈ�v���Ă���A�J�����g�Ȍ�ōł��߂��m�[�h��T��
EffNode* SearchNext_notCrnt(EffList *list, EffNode* n,int comp(const EffNode* x, const EffNode* y))
{
	EffNode* ptr = list->crnt->next;//�����ĊJ�n
	while (list->crnt != ptr) {//������Ă��܂�����I��
		if (ptr != list->head)//�w�b�_�[�͂܂�����
			if (comp(ptr, n) == 0)
				break;
		ptr = ptr->next;
	}
	return ptr;// �T�����������ꍇ�͂��̃m�[�h�A���s�����ꍇ�͌��̃J�����g�m�[�h
};

// �Ȃɂ��̏�����x�ƈ�v���Ă���A�J�����g�ȑO�ōł��߂��m�[�h��T��
EffNode* SearchPrev_notCrnt(EffList *list, EffNode* n, int comp(const EffNode* x, const EffNode* y))
{
	EffNode* ptr = list->crnt->prev;//�����ĊJ�n
	while (list->crnt != ptr) {//������Ă��܂�����I��
		if (ptr != list->head)//�w�b�_�[�͂܂�����
			if (comp(ptr, n) == 0)
				break;
		ptr = ptr->prev;
	}
	return ptr;// �T�����������ꍇ�͂��̃m�[�h�A���s�����ꍇ�͌��̃J�����g�m�[�h
};


// n�ƃm�[�h�̃|�C���^����v���Ă���m�[�h��T��
EffNode* SearchNode(EffList *list, EffNode* n)
{
	EffNode* ptr = list->head->next;
	while (ptr != list->head)
	{
		if (NodeCmp(ptr, n) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};

/*// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const EffList* list)
{
	txtColorChange(getDebugFont(), 191, 95, 191, 63);//�F�ύX
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		EffNode* ptr = list->head->next;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", WINDOW_CENTER_X, WINDOW_CENTER_Y,
			int(sizeof(EffData)));
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->next;		// �㑱�m�[�h�ɒ���
		}
	}
	txtColorChange(getDebugFont(), 255, 255, 255, 255);//�F�ύX
};

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const EffList* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		EffNode* ptr = list->head->prev;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", WINDOW_CENTER_X, WINDOW_CENTER_Y);
		while (ptr != list->head) {
			PrintData(ptr);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};*/

// ���ڃm�[�h�������ɐi�߂�
int Next(EffList* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Prev(EffList* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->prev;
	return 1;
};

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(EffList* list, EffNode* p, const EffData x)
{
	EffNode* ptr = AllocDnode();
	EffNode* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// �擪�Ƀm�[�h��}��
void InsertFront(EffList* list, const EffData x)
{
	InsertAfter(list, list->head, x);
};

// �����Ƀm�[�h��}��
void InsertRear(EffList* list, const EffData x)
{
	InsertAfter(list, list->head->prev, x);
};

// �擪�m�[�h���폜
void RemoveFront(EffList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// �����m�[�h���폜
void RemoveRear(EffList* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// ���ڃm�[�h���폜
void RemoveCurrent(EffList* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// �S�m�[�h���폜
void Clear(EffList* list)
{
	while (!IsEmpty(list))	// ��ɂȂ�܂�
		RemoveFront(list);	// �擪�m�[�h���폜
};

// �m�[�h2���m�[�h1�̒���Ɉړ�
void MoveDnodeAfter(EffNode* p_to, EffNode* p_is) {
	if (p_is != p_to) {
		//(�ǂ�����_�~�[�m�[�h�ł͂Ȃ����̂Ƃ���)

		//p_is�̑O���p_is��Y�ꂳ����
		p_is->prev->next = p_is->next;
		p_is->next->prev = p_is->prev;

		//p_is�ɐV�����O��m�[�h���o��������
		p_is->prev = p_to;
		p_is->next = p_to->next;

		//p_to�Ǝ��̃m�[�h��p_is���o��������
		p_to->next->prev = p_is;
		p_to->next = p_is;
	}
};

// �m�[�h1���m�[�h2�̒��O�Ɉړ�
void MoveDnodeBefore(EffNode* p_is, EffNode* p_to) {
	MoveDnodeAfter(p_to->prev, p_is);
};

// �z�E�d�A�����X�g�̌�n��
void Terminate(EffList* list)
{
	Clear(list);			// �S�m�[�h���폜
	free(list->head);		// �_�~�[�m�[�h���폜
};

//�����[�J���֐�

void initializeEffect(EffList* eff) {
//	srand((unsigned)time(NULL));//randomize

	Initialize(eff);

	InitImage(&eImage[ePARTICLE], getTexture(textureLoaderNS::BIG_STAR), 0.0f,0.0f, 20, 20);
	InitImage(&eImage[eMAGIC], getTexture(textureLoaderNS::MAGIC_CIRCLE), 0.0f,0.0f, 100, 100);
//	eSPLIT�͍ӂ�������摜��Ⴄ�̂ŋ�
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
	eff->crnt = eff->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(eff)) {
		EffData *d = &eff->crnt->effD;
		d->m_time--;
		switch (d->m_type) {
		case ePARTICLE: {
			d->m_rot += 0.008f + 0.116f * float(d->m_time) / float(d->m_tMAX);
			EffData *c2 = &SearchPrev_notCrnt(eff, eff->crnt, DataTypeCmp)->effD//���X�g���őO���ɂ��铯�^�C�v�̃G�t�F�N�g
				, *c3 = &SearchNext_notCrnt(eff, eff->crnt, DataTypeCmp)->effD;//���X�g���Ō���ɂ��铯�^�C�v�̃G�t�F�N�g
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
		if (d->m_time <= 0) RemoveCurrent(eff);//���Ԃ����ς��ɂȂ��č폜
	}
}
void drawEffect(EffList* eff) {
	eff->crnt = eff->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(eff)) {
		EffData *d = &eff->crnt->effD;
		switch (d->m_type) {
		case ePARTICLE:
			setPosition(&d->m_image, d->m_pos.x, d->m_pos.y);//�T�C�Y�̍X�V�����˂Ă���
			setAngleRad(&d->m_image, d->m_rot);
			SetColorImage(&d->m_image, { 1.0f,1.0f,0.5f + 0.5f * float(d->m_time) / float(d->m_tMAX),
				1.5f * float(d->m_time) / float(d->m_tMAX) - 0.25f });//�������F���Ȃ��Ă���
			break;
		case eLUMINE:
			break;
		case eSPLIT:
			movePosition(&d->m_image, d->m_pos.x, d->m_pos.y);//�l�_�̊֌W�͕ێ����Ĉړ������s��
			SetColorImage(&d->m_image, { 0.6f * float(d->m_time) / float(d->m_tMAX),0.6f * float(d->m_time) / float(d->m_tMAX),0.5f,
				3.0f * float(d->m_time) / float(d->m_tMAX)});//���Ȃ��Ă����Ō�Ɉ�C�ɏ�����
			break;
		case eTAIL:
			setPosition(&d->m_image, d->m_pos.x, d->m_pos.y);//�T�C�Y�̍X�V�����˂Ă���
			setAngleRad(&d->m_image, d->m_rot);
			SetColorImage(&d->m_image, { 1.0f,1.0f,1.0f,float(d->m_time) / float(d->m_tMAX)});//�����Ȃ��Ă���
			break;
		case eMAGIC:
			setPosition(&d->m_image, d->m_pos.x, d->m_pos.y);//�T�C�Y�̍X�V�����˂Ă���
			setAngleRad(&d->m_image, d->m_rot);
			SetColorImage(&d->m_image, { 1.0f,1.0f,1.0f,1.4f * float(d->m_time) / float(d->m_tMAX) - 0.1f });//�����Ȃ��Ă���
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
	for (int i = 0; i < 5; i++) {//5���
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
}//���[�J���֐�

void splitSquare(D3DXVECTOR2 pos2[4], D3DXVECTOR2 posed[4], int n0, int n1, int n2, int n3) {
	pos2[n0] = posed[n0] + (posed[n1] - posed[n0]) * randSplit();//�Â���������
	pos2[n2] = posed[n2] + (posed[n3] - posed[n2]) * randSplit();//�Â���������
	if (rand() % 3 != 0) {
		if (rand() % 2 == 0)
			pos2[n0] = posed[n1];
		else pos2[n2] = posed[n3];
	}
	pos2[n1] = posed[n1]; pos2[n3] = posed[n3];//�Â���������炤
	posed[n1] = pos2[n0]; posed[n3] = pos2[n2];//�V�����������炤
}//���[�J���֐�

void makeSplit(EffList* eff, D3DXVECTOR2 pos, Image image) {
	Image img; D3DXVECTOR2 pos2[4]; D3DXVECTOR2 posed[4]; D3DXVECTOR2 speed; D3DXVECTOR2 accel;
	for (int i = 0; i < 4; i++)
		posed[i] = { 1.0f * float(i % 2),1.0f * float(i / 2) };//������Ԃ�Z���ɃZ�b�g

	for (int i = 0; i < SPLIT_NUM; i++) {//8���

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
		SetTexture(&img, pos2[0], pos2[1], pos2[2], pos2[3]);//�e�N�X�`�����_���W�̕ύX

		for (int j = 0; j < 4; j++) {
			pos2[j].x *= image.width; pos2[j].y *= image.height;
			pos2[j] += pos;
		}
		setVertex(&img, pos2[0], pos2[1], pos2[2], pos2[3]);//�`�撸�_���W�̕ύX

		speed = (pos2[0] + pos2[1] + pos2[2] + pos2[3]) / 4.0f//�l�_�̒��S
			- (pos + D3DXVECTOR2{ image.width / 2.0f,image.height / 2.0f });//�}�`�̒��S������
		speed /= 20.0f;//20�Ŋ���
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