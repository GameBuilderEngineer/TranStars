#include "DynamicClass.h"
#include "Stage.h"

//�N���X
ObjStr* DynamicClass::dynObjPop() {
	if (!getdynObjPopPossive()) return NULL;//�m�ۂł���̈悪���E�ɒB���Ă����炻��ȏ���Ȃ�

	if (v.size() > 1) {
		int i = rand() % v.size();
		if (v[i].m_use == false)//use��false�Ȃ��̂ɂ��܂��ܓ�����΍ė��p
			return &v[i];
	}

	ObjStr o; v.push_back(o);
	return &v.back(); 
}

void DynamicClass::replaceVector() {
	for (ObjStr &i : v)
		deletexBased(&i);//x�����X�g����S�폜

	for (std::vector<ObjStr>::iterator i = v.begin(); i != v.end();) {
		if (i->m_use == false)//use��false�Ȃ��̂�v�������
			i = v.erase(i);	//�J��Ԃ����̗v�f�폜�ɂ���đ��ʂ��ς��C�e���������̂ŁA�߂�l���󂯂�K�v����
		else
			i++;//erase�̖߂�l�͎��̗v�f�Ȃ̂ŁA������󂯂��ꍇ��++���Ȃ��Ă悢
	}

	if (v.capacity() - v.size() > RESIZE_VALUE)
		v.shrink_to_fit();//capacity��size�܂Ō��炷

	v.reserve(min(v.capacity() + RESIZE_VALUE, v.max_size()));//max_size�𒴂��Ȃ��悤��capacity�𑝂₷

	for (ObjStr &i : v)
		setxBased(&i);//x�����X�g�ɍđS�o�^

	int a = 0;
}
void DynamicClass::initialize() { v.reserve(RESIZE_VALUE);}
void DynamicClass::uninitialize() { v.clear(); }//���I�I�u�W�F�N�g�S�폜

void DynamicClass::update() {
	for (ObjStr &i : v) {//���� ���̋L�@�ł�&�̕t�����Q�ƕϐ��Ƃ��Ő錾���Ȃ��Ə����s�\(i�͏�������邪v�̒��g�͏��������Ȃ�)�ɂȂ���ۂ�
		updateObject(&i);
	}
	if (v.capacity() - v.size() <= RESIZE_LEVEL)
		replaceVector();
}

void DynamicClass::draw() {
	for (ObjStr &i : v)
		drawObject(&i);
}

void DynamicClass::print() {
	for (ObjStr &i : v)
		printObject(&i);
}
