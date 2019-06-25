#pragma once

#include "object.h"
#include <vector>

#define RESIZE_VALUE (10)//�R���e�i�����̈�́A�Ċm�ۗ�
#define RESIZE_LEVEL (RESIZE_VALUE * 1 / 5)//�R���e�i�����̈�́A�Ċm�ۂ��s���l(RESIZE_NUM�ȉ�)

class DynamicClass {
private:
	std::vector<ObjStr> v;//���I�I�u�W�F�N�g
	void replaceVector();//v.�̒���x�����X�g���Ĕz�u
public:
	void initialize();
	void uninitialize();
	void update();
	void draw();
	void print();
	std::vector<ObjStr>* getDynObj() { return &v; }
	int getDynObjNum() { return v.size(); }
	bool getdynObjPopPossive() { return v.size() < v.max_size(); }
	ObjStr* dynObjPop();//�����ɒǉ����ă|�C���^��Ԃ�
};
