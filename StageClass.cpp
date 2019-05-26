#include "StageClass.h"
using namespace stageNS;

void StageClass::initialize(int stage)
{
	getFileLoader()->load(STAGE_NAME[stage]);//指定したステージ番号を読み込む
	m_OBJNUM = getFileLoader()->objNum();//ファイルローダーからオブジェクトの数を取得
	SAFE_DELETE_ARRAY (m_Obj);//新規初期化する前に削除
	m_Obj = new ObjStr[m_OBJNUM];//動的確保
	Object* o = getFileLoader()->getObj();//省略するために、ポインタ取得
	for (int i = 0; i < m_OBJNUM; i++)
	{//確保されたオブジェクトの初期化
		initializeObject(&m_Obj[i], o[i].id, o[i].objType, o[i].position, o[i].rotation);
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