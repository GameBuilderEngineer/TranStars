#pragma once
// �z�E�d�A�����X�g(�w�b�_��)

#include "object.h"
#include "effect.h"

enum funcTypes {
	FUNC_NO_TYPE = -1,
	FUNC_COLLISION,
	FUNC_ACTION,
	FUNC_ACTION_EFFECT
};

// �֐����ꂽ���p��
typedef union {
	void (*_n);//FUNC_NO_TYPE
	bool (*_b)(ObjStr* a, ObjStr* b);//FUNC_COLLISION
	void (*_v)(ObjStr* a, ObjStr* b);//FUNC_ACTION
	void (*_ef)(ObjStr* a, ObjStr* b, EffList* eff);//FUNC_ACTION_EFFECT
}UnionFunc;

//�f�[�^
typedef struct {
	objTypes m_type1;					// �I�u�W�F�N�g�^�C�v1
	objTypes m_type2;					// �I�u�W�F�N�g�^�C�v2
	bool m_use;							// ���̊֐���1����2�Ɋ����邩

	funcTypes fType;					// �֐��^
	UnionFunc mp_func;					// �g���֐�
}TF_Data;

// �m�[�h
typedef struct __node_tf {
	TF_Data d;
	struct __node_tf *prev;			// �O�m�[�h�ւ̃|�C���^
	struct __node_tf *next;			// ��m�[�h�ւ̃|�C���^
}TF_Node;

// �z�E�d�A�����X�g
typedef struct {
	TF_Node *head;						// �擪(���[)�_�~�[�m�[�h�ւ̃|�C���^
	TF_Node *crnt;						// ���ڃm�[�h�ւ̃|�C���^
}TF_List;

// ���X�g��������
void Initialize(TF_List *list);

// (x1,x2)�Ɗ֌W�^�C�v����v���Ă���m�[�h��T��
TF_Node* SearchNextTF_byObjType(TF_List *list, const objTypes x1, const objTypes x2);
// n�ƃm�[�h�̃|�C���^����v���Ă���m�[�h��T��
TF_Node* SearchTF_Node(TF_List *list, TF_Node* n);
// d�ƃf�[�^�̑S�����o����v���Ă���m�[�h��T��
TF_Node* SearchTF_Data(TF_List *list, TF_Data* d);

/*// �S�m�[�h�̃f�[�^�����X�g���ɕ\��
void Print(const TF_List* list);

// �S�m�[�h�̃f�[�^�����X�g�̋t���ɕ\��
void PrintReverse(const TF_List* list);

// �f�[�^�̕\���i���s�Ȃ��j
void PrintData(const TF_Node* n);
void PrintTypeFunc(const TF_Node* n);*/

// ���ڃm�[�h�������ɐi�߂�
int Next(TF_List* list);

// ���ڃm�[�h����O���ɖ߂�
int Prev(TF_List* list);

// p���w���m�[�h�̒���Ƀm�[�h��}��
void InsertAfter(TF_List* list, TF_Node* p, const TF_Data x);

// �擪�Ƀm�[�h��}��
void InsertFront(TF_List* list, const TF_Data x);

// �����Ƀm�[�h��}��
void InsertRear(TF_List* list, const TF_Data x);

// �擪�m�[�h���폜
void RemoveFront(TF_List* list);

// �����m�[�h���폜
void RemoveRear(TF_List* list);

// ���ڃm�[�h���폜
void RemoveCurrent(TF_List* list);

// �S�m�[�h���폜
void Clear(TF_List* list);

// �z�E�d�A�����X�g�̌�n��
void Terminate(TF_List* list);

// 2�̃^�C�v�Ause�t���O�̏�����ԁA�p����֐������X�g�ɓo�^
void setTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func);
// �����Ε���(type1L<=type1<=type1H��type2L<=type2<=type2H)�̃^�C�v�֌W�Q�ƁAuse�t���O�̏�����ԁA�p����֐������X�g�ɓo�^
void setTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func);
// �����ɍ������̂��^�C�v���X�g�������
void deleteTypeFunc(TF_List* list, objTypes type1, objTypes type2, bool use, funcTypes fType, UnionFunc p_func);//
// �����ɍ������̂��^�C�v���X�g�������
void deleteTypeFuncs(TF_List* list, objTypes type1L, objTypes type1H, objTypes type2L, objTypes type2H, bool use,
	funcTypes fType, UnionFunc p_func);

// �^�C�v���X�g����A�^�C�v�������t�ɂȂ��Ă邾���Ȃ��̂�����
void optimizeTypeFuncs(TF_List* list);

UnionFunc castFunc(static bool(*p_func)(ObjStr* a, ObjStr* b));
UnionFunc castFunc(static void(*p_func)(ObjStr* a, ObjStr* b));
UnionFunc castFunc(static void(*p_func)(ObjStr* a, ObjStr* b,EffList* eff));

