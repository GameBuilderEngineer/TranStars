#pragma once

#include "object.h"
#include "fileLoader.h"

namespace stageNS {
	enum
	{
		STAGE01,
		STAGE02,
		STAGE03,
		STAGE04,
		STAGE05,
		STAGE06,
		STAGE07,
		STAGE08,
		STAGE09,
		STAGE10,
		STAGE11,
		STAGE12,
		STAGE_NUM,
	};
	const LPSTR STAGE_NAME[STAGE_NUM] =
	{
		(LPSTR)"stage/stage01.txt",
		(LPSTR)"stage/stage02.txt",
		(LPSTR)"stage/stage03.txt",
		(LPSTR)"stage/stage04.txt",
		(LPSTR)"stage/stage05.txt",
		(LPSTR)"stage/stage06.txt",
		(LPSTR)"stage/stage07.txt",
		(LPSTR)"stage/stage08.txt",
		(LPSTR)"stage/stage09.txt",
		(LPSTR)"stage/stage10.txt",
		(LPSTR)"stage/stage11.txt",
		(LPSTR)"stage/stage12.txt",
	};
}

class StageClass
{
private:
	int m_STAGE;		//ステージ番号
	int m_OBJNUM;		//オブジェクト数
	ObjStr *m_Obj;		//オブジェクト
	int m_CLEARNUM;		//西川0531 クリアに必要な星の数
	int m_starNum;		//西川0531 枠にはまった星の数
public:
	//int stage:ステージ番号
	void initialize(int stage);
	void uninitialize();
	void update();
	void draw();
	void print();
	int getObjNum() { return m_OBJNUM;}
	ObjStr* getObj() { return m_Obj;}
	int getClearNum() { return m_CLEARNUM; }//西川0531 クリアに必要な星の数取得
	bool starNumPluss() {
		m_starNum++;//はまった星の数++
		if (m_starNum >= m_CLEARNUM) return true;
		else return false;
	}
};