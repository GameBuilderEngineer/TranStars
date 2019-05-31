#include "funcTypeList.h"
#include "textDX.h"

// ��̃m�[�h�𓮓I�ɐ���
static TF_Node* AllocDnode(void)
{
	return (TF_Node*)calloc(1, sizeof(TF_Node));
}

// �m�[�h�̊e�����o�ɒl��ݒ�
static void SetDnode(TF_Node* n, const TF_Data x, TF_Node* prev, TF_Node* next)
{
	n->d = x;
	n->prev = prev;		// ��s�m�[�h�ւ̃|�C���^
	n->next = next;		// �㑱�m�[�h�ւ̃|�C���^
}

// �֐��^���Ƃ̊֐����Z�b�g
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
// �f�[�^���Z�b�g
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
	default://���݂��Ȃ��^
		SetTF_NoType(&d);
		break;
	}
	return d;
}


// ���X�g�͋�
static int IsEmpty(const TF_List* list)
{
	return list->head->next == list->head;
}

// p���w���m�[�h���폜
void Remove(TF_List* list, TF_Node* p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	list->crnt = p->prev;	// �폜�����m�[�h�̐�s�m�[�h�ɒ���
	free(p);
//	if (list->crnt == list->head)
//		list->crnt = list->head->next;
};

// �^�C�v���r����
static int typeCmp(const objTypes x, const objTypes y) {
	return x < y ? -1 : x > y ? 1 : 0;	//2�̃f�[�^�������^�C�v�̑g�ݍ��킹�������̂ł����
}
// �^�C�v������ȃ^�C�v�ł���Ό��o(true)����
static bool detectNoType(const objTypes t) {
	if (int(t) < int(NO_TYPE) || t == NO_TYPE || t == TYPE_MAX || int(TYPE_MAX) < int(t)) return true;
	return false;
}
//�@�^�C�v�̑召��type1���������Ȃ�悤�ɑ�����
void sortType(objTypes* t1, objTypes* t2) {
	if (int(*t1) > int(*t2)) {
		objTypes s = *t1;
		*t1 = *t2; *t2 = s;
	}
}

// �f�[�^�S�̂��r
static int dataCmp(const TF_Data* d1, const TF_Data* d2) {
	return d1->m_type1 != d2->m_type1 ? 1 : d1->m_type2 != d2->m_type2 ? 1 : d1->m_use != d2->m_use ? 1 : d1->fType != d2->fType ? 1 : d1->mp_func._n != d2->mp_func._n ? 1
		: 0;//�S���ꏏ�Ȃ�0
};


// �m�[�h�̃|�C���^�̔�r�֐�
int NodeCmp(const TF_Node* x, const TF_Node* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};
// �֐��^�̊m�F�֐�
int FuncTypeCmp(const TF_Data* x, const TF_Data* y)
{
	return x->fType < y->fType ? -1 : x->fType > y->fType ? 1 : 0;
};
// ���X�g�̊m�F�֐�
int TF_ListCmp(const TF_List* x, const TF_List* y)
{
	return x < y ? -1 : x > y ? 1 : 0;
};

//�����[�J���֐�

// ���X�g��������
void Initialize(TF_List* list)
{
	TF_Node* dummyNode = AllocDnode(); // �_�~�[�m�[�h�𐶐�
	list->head = list->crnt = dummyNode;
	dummyNode->prev = dummyNode->next = dummyNode;

	SetTF_NoType(&dummyNode->d);
}

TF_Node* SearchNextTF_byObjType(TF_List *list, const objTypes x1, const objTypes x2)
{
	TF_Node* ptr = list->crnt->next;//�J�����g�̎�����o��
	while (ptr != list->head)
	{
		if (typeCmp(ptr->d.m_type1, x1) == 0 && typeCmp(ptr->d.m_type2, x2) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};
TF_Node* SearchTF_Node(TF_List *list, TF_Node* n)
{
	TF_Node* ptr = list->head->next;
	if (FuncTypeCmp(&ptr->d, &n->d) != 0) return NULL;//�f�[�^�^��������玸�s
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
TF_Node* SearchTF_Data(TF_List *list, TF_Data* d)
{
	TF_Node* ptr = list->head->next;
	if (FuncTypeCmp(&ptr->d, d) != 0) return NULL;//�f�[�^�^��������玸�s
	while (ptr != list->head)
	{
		if (dataCmp(&ptr->d, d) == 0)
		{
			list->crnt = ptr;
			return ptr;			// �T������
		}
		ptr = ptr->next;
	}
	return NULL;				// �T�����s
};

/*
// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const TF_List* list)
{
	txtColorChange(getDebugFont(), 191, 95, 191, 63);//�F�ύX
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		TF_Node* ptr = list->head->next;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", WINDOW_CENTER_X, WINDOW_CENTER_Y, int(sizeof(NULL)));//�f�[�^�T�C�Y
		while (ptr != list->head) {
			PrintTF(ptr);
			ptr = ptr->next;		// �㑱�m�[�h�ɒ���
		}
	}
	txtColorChange(getDebugFont(), 255, 255, 255, 255);//�F�ύX
};

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const TF_List* list)
{
	if (IsEmpty(list))
		printTextDX(getDebugFont(), "�m�[�h������܂���B", WINDOW_CENTER_X, WINDOW_CENTER_Y);
	else {
		TF_Node* ptr = list->head->prev;
		printTextDX(getDebugFont(), "�y�ꗗ�\�z", WINDOW_CENTER_X, WINDOW_CENTER_Y);
		while (ptr != list->head) {
			PrintTF(ptr);
			ptr = ptr->prev;		// ��s�m�[�h�ɒ���
		}
	}
};

// �f�[�^�̕\��
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
	default://���݂��Ȃ��^
		printTextDX(getDebugFont(), "�H", WINDOW_CENTER_X, txtLineReset(txtLineReset(0)));
		break;
	}
}

void PrintTF_Collision(const TF_Node* n)
{
	txtLineReset(txtLineReset(0));

	printTextDX(getDebugFont(), "��type�F", 0, txtLineBreak(), int(n->d.m_type1));
	printTextDX(getDebugFont(), "��type�F", 0, txtLineBreak(), int(n->d.m_type2));
	if (n->d.m_use == true) printTextDX(getDebugFont(), "�L��", 0, txtLineBreak());
	else printTextDX(getDebugFont(), "����", 0, txtLineBreak());
};
*/

// ���ڃm�[�h�������ɐi�߂�
int Next(TF_List* list)
{
	if (IsEmpty(list) || list->crnt->next == list->head)
		return 0;	// �i�߂邱�Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->next;
	return 1;
};

// ���ڃm�[�h����O���ɖ߂�
int Prev(TF_List* list)
{
	if (IsEmpty(list) || list->crnt->prev == list->head)
		return 0;	// �߂����Ƃ͂ł��Ȃ�
	list->crnt = list->crnt->prev;
	return 1;
};

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(TF_List* list, TF_Node* p, const TF_Data x)
{
	TF_Node* ptr = AllocDnode();
	TF_Node* nxt = p->next;
	p->next = p->next->prev = ptr;
	SetDnode(ptr, x, p, nxt);
	list->crnt = ptr;
};

// �擪�Ƀm�[�h��}��
void InsertFront(TF_List* list, const TF_Data x)
{
	InsertAfter(list, list->head, x);
};

// �����Ƀm�[�h��}��
void InsertRear(TF_List* list, const TF_Data x)
{
	InsertAfter(list, list->head->prev, x);
};

// �擪�m�[�h���폜
void RemoveFront(TF_List* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->next);
};

// �����m�[�h���폜
void RemoveRear(TF_List* list)
{
	if (!IsEmpty(list))
		Remove(list, list->head->prev);
};

// ���ڃm�[�h���폜
void RemoveCurrent(TF_List* list)
{
	if (list->crnt != list->head)
		Remove(list, list->crnt);
};

// �S�m�[�h���폜
void Clear(TF_List* list)
{
	while (!IsEmpty(list))	// ��ɂȂ�܂�
		RemoveFront(list);	// �擪�m�[�h���폜
};

// �z�E�d�A�����X�g�̌�n��
void Terminate(TF_List* list)
{
	if (list->head != NULL) {
		Clear(list);			// �S�m�[�h���폜
		free(list->head);		// �_�~�[�m�[�h���폜
	}
};


// 2�̃^�C�v�Ause�t���O�̏�����ԁA�p����֐���o�^
void setTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func) {
	if (!detectNoType(type1) && !detectNoType(type2)) {//NoType�Ȃ�true
		InsertRear(list, SetTF_Data(type1, type2, use, fType, p_func));
	}
}

// �����Ε���(type1L<=type1<=type1H��type2L<=type2<=type2H)�̃^�C�v�֌W�Q�ƁAuse�t���O�̏�����ԁA�p����֐���o�^
void setTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func) {
	//setTypeFunc���ʂɏ��O����̂ŁA���[�ɂ�NO_TYPE�Ƃ������Ă��\��Ȃ�
	for (int i = int(type1L); i <= int(type1H); i++)
		for (int j = int(type2L); j <= int(type2H); j++) {
			TF_Data d = SetTF_Data(objTypes(i), objTypes(j), use, fType, p_func);
			if (SearchTF_Data(list, &d) == NULL)//���������͂܂��Ȃ�������
				setTypeFunc(list, objTypes(i), objTypes(j), use, fType, p_func);
		}
}

// 2�̃^�C�v�Ause�t���O�̏�����ԁA�p����֐����폜
void deleteTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func) {
	TF_Data d = SetTF_Data(type1, type2, use, fType, p_func);
	if (!detectNoType(type1) && !detectNoType(type2))//NoType�Ȃ�true
		if (SearchTF_Data(list, &d) != NULL)//������������������A�������J�����g�ɂȂ�̂�
			Remove(list, list->crnt);
}

// �����Ε���(type1L<=type1<=type1H��type2L<=type2<=type2H)�̃^�C�v�֌W�Q�ƁAuse�t���O�̏�����ԁA�p����֐����폜
void deleteTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func) {
	//deleteTypeFunc���ʂɏ��O����̂ŁA���[�ɂ�NO_TYPE�Ƃ������Ă��\��Ȃ�
	for (int i = int(type1L); i <= int(type1H); i++)
		for (int j = int(type2L); j <= int(type2H); j++)
			deleteTypeFunc(list, objTypes(i), objTypes(j), use, fType, p_func);
}

//�œK��
void optimizeTypeFuncs(TF_List* list) {
	TF_Node* n = list->head->next;
	for (int i = int(NO_TYPE) + 1; i <= int(TYPE_MAX) - 1; i++)
		for (int j = i + 1; j < int(TYPE_MAX); j++)
			while (n != NULL) {
				deleteTypeFunc(list, objTypes(i), objTypes(j), n->d.m_use,n->d.fType, n->d.mp_func);
				//�^�C�v�̑g�ݍ��킹���t�ŏ������ꏏ�Ȃ��̂�T���č폜
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
