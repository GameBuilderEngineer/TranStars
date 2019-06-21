#include "StageClass.h"
using namespace stageNS;

void StageClass::initialize(int stage)
{
	getFileLoader()->load(STAGE_NAME[stage]);//�w�肵���X�e�[�W�ԍ���ǂݍ���
	m_OBJNUM = getFileLoader()->objNum();//�t�@�C�����[�_�[����I�u�W�F�N�g�̐����擾
	SAFE_DELETE_ARRAY (m_Obj);//�V�K����������O�ɍ폜
	m_Obj = new ObjStr[m_OBJNUM];//���I�m��
	Object* o = getFileLoader()->getObj();//�ȗ����邽�߂ɁA�|�C���^�擾
	m_CLEARNUM = 0; m_starNum = 0;
	for (int i = 0; i < m_OBJNUM; i++)
	{//�m�ۂ��ꂽ�I�u�W�F�N�g�̏�����
		initializeObject(&m_Obj[i], o[i].id, o[i].objType, o[i].position, o[i].rotation,m_Obj,m_OBJNUM);

		if (m_Obj[i].m_type == CHARA_SMALL_STARFRAME || m_Obj[i].m_type == CHARA_SMALL_STARFRAME) {
			m_CLEARNUM++;//�N���A�ɕK�v�Șg�̐�++
		}
	}
}

void StageClass::uninitialize()
{
	SAFE_DELETE_ARRAY (m_Obj);
	getFileLoader()->release();
}

void StageClass::update()
{
	for (int i = 0; i < m_OBJNUM; i++)
	{
		updateObject(&m_Obj[i]);
	}
}

void StageClass::draw()
{
	for (int i = 0; i < m_OBJNUM; i++)
	{
		drawObject(&m_Obj[i]);
	}
}
void StageClass::print()
{
	for (int i = 0; i < m_OBJNUM; i++)
	{
		printObject(&m_Obj[i]);
	}
}
