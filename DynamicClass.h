#pragma once

#include "object.h"
#include <vector>

class DynamicClass {
private:
	std::vector<ObjStr> v;//���I�I�u�W�F�N�g
	void deleteObj(ObjStr* i);//v.�̒��ɂ���I�u�W�F�N�g���ǂ����m���߂Ă��Ȃ��̂ŊO�ł͎g���������
public:
	void initialize();
	void uninitialize();
	void update();
	void draw();
	void print();
	std::vector<ObjStr>* getDynObj() { return &v; }
	int getDynObjNum() { return v.size(); }
	ObjStr* dynObjPop() { ObjStr o; v.push_back(o); return &v.back(); }//�����ɒǉ����ă|�C���^��Ԃ�
};
