#include "effect.h"
#include "textDX.h"
#include "image.h"
#include "textureLoader.h"

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
	if (list->crnt == list->head)
		list->crnt = list->head->next;
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

// �f�[�^�̕\��
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
}

// x�ƃf�[�^�̃^�C�v����v���Ă���A�J�����g�Ȍ�ōł��߂��m�[�h��T��
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

// x�ƃf�[�^�̃^�C�v����v���Ă���A�J�����g�ȑO�ōł��߂��m�[�h��T��
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
//			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};

// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
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
};

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
	if (list->head != NULL) {
		Clear(list);			// �S�m�[�h���폜
		free(list->head);		// �_�~�[�m�[�h���폜
		list->head = NULL;
	}
};

//�����[�J���֐�

void initializeEffect(EffList* eff) {
	Initialize(eff);
}
void uninitializeEffect(EffList* eff) {
	Terminate(eff);
}
void updateEffect(EffList* eff) {
	eff->crnt = eff->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(eff)) {
		EffData *c = &eff->crnt->effD;
		c->m_time--;
		switch (c->m_type) {
		case ePARTICLE: {
			c->m_rot += 0.5f + 7.0f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX);
			EffData *c2 = &SearchPrev_notCrnt(eff, eff->crnt, DataTypeCmp)->effD//���X�g���őO���ɂ��铯�^�C�v�̃G�t�F�N�g
				, *c3 = &SearchNext_notCrnt(eff, eff->crnt, DataTypeCmp)->effD;//���X�g���Ō���ɂ��铯�^�C�v�̃G�t�F�N�g
			c->m_accel = ((c2->m_pos + c3->m_pos) / 2.0f - c->m_pos) / 1000.0f;
			c->m_speed += c->m_accel;
			c->m_pos += c->m_speed;
			SetColorImage(&eff->crnt->effD.m_image,
				{ 1.0f,1.0f,0.5f + 0.5f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX),
				1.5f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX) - 0.25f });//�������F���Ȃ��Ă���
			break;
		}
		case eLUMINE:
			break;
		case eSPLIT:
			break;
		case eTAIL:
			break;
		case eMAGIC: {
			c->m_rot += 0.5f + 7.0f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX);
			float f = 35.0f * float(eff->crnt->effD.m_time - eff->crnt->effD.m_tMAX * 2 / 3) / (float)eff->crnt->effD.m_tMAX;
			c->m_image.width += (int)f;
			c->m_image.height += (int)f;
			c->m_pos = { c->m_pos.x - f / 2.0f ,c->m_pos.y - f / 2.0f };
			SetColorImage(&eff->crnt->effD.m_image,
				{ 1.0f,1.0f,1.0f,1.4f * float(eff->crnt->effD.m_time) / float(eff->crnt->effD.m_tMAX) - 0.1f });//�����Ȃ��Ă���
			break;
		}
		default:
			break;
		}
		if (c->m_time <= 0) RemoveCurrent(eff);//���Ԃ����ς��ɂȂ��č폜
	}
}
void drawEffect(EffList* eff) {
	eff->crnt = eff->head;// ���X�g�̒��ڃm�[�h�����Z�b�g
	while (Next(eff)) {
		setPosition(&eff->crnt->effD.m_image, eff->crnt->effD.m_pos.x, eff->crnt->effD.m_pos.y);//�T�C�Y�̍X�V�����˂Ă���
		setAngle(&eff->crnt->effD.m_image, eff->crnt->effD.m_rot);
		DrawImage(&(eff->crnt->effD.m_image));
	}
}


void makeParticle(EffList* eff, D3DXVECTOR2 pos) {
	Image img; float c; D3DXVECTOR2 speed;
	for (int i = 0; i < 5; i++) {//5���
		c = float(rand() % 100) * D3DX_PI / 50.0f;
		speed = { 5.0f * cosf(c), 5.0f * sinf(c) };

		InitImage(&img, getTexture(textureLoaderNS::STAR3), pos.x, pos.y, 20, 20);
		InsertRear(eff, { ePARTICLE, true, {pos.x - img.width / 2,pos.y- img.height / 2}, c, { 1.0f, 1.0f}, speed, { 0.0f, 0.0f }, 100, 100, 0, img });

		pos += {float(rand() % 31 - 15), float(rand() % 31 - 15)};
	}
}

void makeMagic(EffList* eff, D3DXVECTOR2 pos) {
	Image img; float c;
	c = float(rand() % 100) * D3DX_PI / 50.0f;
	InitImage(&img, getTexture(textureLoaderNS::MAGIC_CIRCLE), pos.x, pos.y, 100, 100);
	InsertRear(eff, { eMAGIC, true, {pos.x - img.width / 2 ,pos.y - img.height / 2}, c, { 1.0f, 1.0f}, { 0.0f, 0.0f }, { 0.0f, 0.0f }, 40, 40, 0, img });
}
