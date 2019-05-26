#pragma once
#include "main.h"
#include "Image.h"

// �G�t�F�N�g��

// �^�C�v
enum effTypes {
	eNO_TYPE = -1,
		ePARTICLE,//���̗�
		eLUMINE,//����
		eSPLIT,//�����
		eTAIL,//覐΂̔�
		eMAGIC,//���@�w
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
void updateEffect(EffList* eff);
void drawEffect(EffList* eff);

void makeParticle(EffList* eff, D3DXVECTOR2 pos);
void makeMagic(EffList* eff, D3DXVECTOR2 pos);