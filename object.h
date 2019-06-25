//����
#pragma once

#include "main.h"
#include "Image.h"
#include"textureLoader.h"

enum objTypes{
	NO_TYPE = -1,
		CHARA_BLACKHOLE,
		CHARA_WHITEHOLE,
		UI_CURSOR,
		CHARA_SMALL_STAR,
		CHARA_BIG_STAR,
		CHARA_COMET,
		POP_STAR,
		POP_COMET,
		CHARA_SMALL_STARFRAME,
		CHARA_BIG_STARFRAME,
		CHARA_STARDUST,
		STAGE_STARLINE,
		STAGE_REFLECTION,
	TYPE_MAX,//����0525
};

//short��-0.5�}32767.5�Aint��-0.5�}2147483647.5������

//************************************************************************
//�I�u�W�F�N�g�̈���
// �Ƃ肠���������o�ϐ��͎b��B�K�v�ɉ����đ��₵���茸�炵���肷�邩���B
// ���̏ꍇ�͊֘A����(�֐��Ƃ�)�C�����Ă����Ƃ��肪�����B
//************************************************************************
typedef struct _obj{
	objTypes m_type;					//�I�u�W�F�N�g�^�C�v
	short	 m_id;						//�S�^�C�v�������Ă���z����́A�����̔ԍ�
	bool	 m_use;						//use�t���O
	_obj*	 m_ptr;						//���g�ւ̃|�C���^
	_obj*	 m_tar;						//�^�[�Q�b�g�̃|�C���^(��{�̓u���b�N�z�[��)
	int		targetNum;					//�^�[�Q�b�g�̐�
	_obj*	 whiteHole;						//�z���C�g�z�[���ւ̃|�C���^


	D3DXVECTOR2	m_pos;					//���W
	float		m_rot;					//�p�x
	D3DXVECTOR2 m_scl;					//�傫��

	D3DXVECTOR2 m_speed;				//���x
	D3DXVECTOR2 m_accel;				//�����x(���̃I�u�W�F�N�g����y�ڂ����́A�����Ƃ�)
	D3DXVECTOR2 m_attract;				//���́@(�����ȊO�̃I�u�W�F�N�g�ɋy�ڂ��͂Ƃ�)

	float	m_time;						//�v���C���[�Ƃ͓Ɨ����ď���ɓ����I�u�W�F�N�g������Ύg��(�X�e�[�W�M�~�b�N�n)
	short	m_mode;						//����A�s���p�^�[���Ƃ��͂�����
	bool	onAttract;					//���͂̉e�����󂯂邩�ǂ���

	float m_rad;						//���a(�v���C���[�̓����蔻��Ƃ�)
	D3DXVECTOR2 m_rect;					//��`�̕Ӓ�(�X�e�[�W�̓����蔻��Ƃ�)
	D3DXVECTOR2	m_corner[4];			// �Փ˃{�b�N�X�̊e���_�ɑ΂���x�N�g��

	//�ՓˈȊO�ł��g���Ȃ�z��ɂȂ邩��(�ߊ��Ɠ����o���Ƃ��A�u���b�N�z�[�����z���񂹎n�߂�͈͂Ƃ�)

	Image m_image;						//�`����
}ObjStr;//Structure

#define SPEED_FRICTION (0.975f)

#define STUB_OBJNUM (100)	//�X�e�[�W�̃f�[�^���ɂ���I�u�W�F�N�g�̑���/���ۂɂ͊O������炤�l
#define PLUS_OBJNUM (5)		//�X�e�[�W���ŕۑ�����K�v�̂Ȃ��I�u�W�F�N�g���(UI�Ȃ�)������΂���̐�


void initializeObject(ObjStr *obj, int id, int objType, VECTOR2 position, float angle, ObjStr* others, int otherNum);
void uninitializeObject(ObjStr* obj);
void updateObject(ObjStr* obj);
void drawObject(ObjStr* obj);
void printObject(ObjStr* obj);

float getObjectHarfSizeLonger(ObjStr* obj);//����0519  �I�u�W�F�N�g�̎������o�̂����A��`�̑Ίp���Ɣ��a�Œ�������Ԃ�
D3DXVECTOR2 getImageHarf(Image* image);//�摜�̔����̃T�C�Y(���S�_)�𓾂�
D3DXVECTOR2 getObjectFar_PosToCenter(ObjStr* obj);//�I�u�W�F�N�g�̍���ƒ��S�̋���
D3DXVECTOR2 getObjectFar_PosToCorner(ObjStr* obj);//�I�u�W�F�N�g�̍���ƉE���̋���
D3DXVECTOR2 getObjectCenter(ObjStr* obj);//�I�u�W�F�N�g�̒��S(���ꌩ��)

// �I�u�W�F�N�g1�ɑ΂���I�u�W�F�N�g2�̕����x�N�g����߂�
D3DXVECTOR2 objectDirection(ObjStr* p_obj1, ObjStr* p_obj2);
//2�̃I�u�W�F�N�g�Ԃ̋������v�Z
float objectLength(ObjStr* p_obj1, ObjStr* p_obj2);				

void setWhiteHole(ObjStr* obj, ObjStr* whiteHole);
