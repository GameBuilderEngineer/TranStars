#pragma once

#include "object.h"
#include <vector>

#define RESIZE_VALUE (10)//コンテナが持つ領域の、再確保量
#define RESIZE_LEVEL (RESIZE_VALUE * 1 / 5)//コンテナが持つ領域の、再確保を行う値(RESIZE_NUM以下)

class DynamicClass {
private:
	std::vector<ObjStr> v;//動的オブジェクト
	void replaceVector();//v.の中とx順リストを再配置
public:
	void initialize();
	void uninitialize();
	void update();
	void draw();
	void print();
	std::vector<ObjStr>* getDynObj() { return &v; }
	int getDynObjNum() { return v.size(); }
	bool getdynObjPopPossive() { return v.size() < v.max_size(); }
	ObjStr* dynObjPop();//末尾に追加してポインタを返す
};
