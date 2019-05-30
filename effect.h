#pragma once
#include "main.h"
#include "object.h"

// �G�t�F�N�g��

// �^�C�v
enum effTypes {
	eNO_TYPE = -1,
		ePARTICLE,//���̗�
		eLUMINE,//����
		eSPLIT,//�����
		eTAIL,//覐΂̔�
		eMAGIC,//���@�w
		eDISTORT,//�c��
	eTYPE_MAX
};

// �f�[�^
typedef struct {
	effTypes m_type;					//�G�t�F�N�g�^�C�v
	bool	 m_use;						//use�t���O

	D3DXVECTOR2	m_pos;					//���W
	float		m_rot;					//�p�x
	D3DXVECTOR2 m_scl;					//�傫��

	D3DXVECTOR2 m_speed;				//���x
	D3DXVECTOR2 m_accel;				//�����x

	int		m_time;						//�o�ߎ���
	int		m_tMAX;						//�o�ߎ���MAX
	short	m_mode;						//�i�K

	Image m_image;						//�`����
//	ObjStr* mp_obj;						//����̃I�u�W�F�N�g
}EffData;

// �m�[�h
typedef struct __node_eff {
	EffData effD;
	struct __node_eff *prev;			// �O�m�[�h�ւ̃|�C���^
	struct __node_eff *next;			// ��m�[�h�ւ̃|�C���^
}EffNode;

// �z�E�d�A�����X�g
typedef struct {
	EffNode *head;						// �擪(���[)�_�~�[�m�[�h�ւ̃|�C���^
	EffNode *crnt;						// ���ڃm�[�h�ւ̃|�C���^
}EffList;

void initializeEffect(EffList* eff);
void uninitializeEffect(EffList* eff);
void startEffect(EffList* eff);
void finishEffect(EffList* eff);

void updateEffect(EffList* eff);
void drawEffect(EffList* eff);


void makeParticle(EffList* eff, D3DXVECTOR2 pos);
void makeMagic(EffList* eff, D3DXVECTOR2 pos);
void makeSplit(EffList* eff, D3DXVECTOR2 pos, Image image);
void makeTail(EffList* eff, D3DXVECTOR2 pos, D3DXVECTOR2 speed);
void makeEffect(EffList* eff, effTypes eType, ObjStr* obj);