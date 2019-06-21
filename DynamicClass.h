#pragma once

#include "object.h"
#include <vector>

class DynamicClass {
private:
	std::vector<ObjStr> v;//動的オブジェクト
	void deleteObj(ObjStr* i);//v.の中にあるオブジェクトかどうか確かめていないので外では使わん方が無難か
public:
	void initialize();
	void uninitialize();
	void update();
	void draw();
	void print();
	std::vector<ObjStr>* getDynObj() { return &v; }
	int getDynObjNum() { return v.size(); }
	ObjStr* dynObjPop() { ObjStr o; v.push_back(o); return &v.back(); }//末尾に追加してポインタを返す
};
