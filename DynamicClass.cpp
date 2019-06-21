#include "DynamicClass.h"

//�N���X
void DynamicClass::deleteObj(ObjStr* i) {
	ObjStr s = *i;
	*i = v.back();
	v.back() = s;
	i->m_id = s.m_id;
	v.pop_back();
}

void DynamicClass::initialize() {}
void DynamicClass::uninitialize() { v.clear(); }//���I�I�u�W�F�N�g�S�폜

void DynamicClass::update() {
	for (ObjStr &i : v) {//���� ���̋L�@�ł�&�̕t�����Q�ƕϐ��Ƃ��Ő錾���Ȃ��Ə����s�\(i�͏�������邪v�̒��g�͏��������Ȃ�)�ɂȂ���ۂ�
		updateObject(&i);
		if (i.m_use == false)
			deleteObj(&i);
	}
}

void DynamicClass::draw() {
	for (ObjStr &i : v)
		drawObject(&i);
}

void DynamicClass::print() {
	for (ObjStr &i : v)
		printObject(&i);
}
