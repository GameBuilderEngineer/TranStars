#include "DynamicClass.h"

//クラス
void DynamicClass::deleteObj(ObjStr* i) {
	ObjStr s = *i;
	*i = v.back();
	v.back() = s;
	i->m_id = s.m_id;
	v.pop_back();
}

void DynamicClass::initialize() {}
void DynamicClass::uninitialize() { v.clear(); }//動的オブジェクト全削除

void DynamicClass::update() {
	for (ObjStr &i : v) {//西川 この記法では&の付いた参照変数とやらで宣言しないと書換不能(iは書き換わるがvの中身は書き換わらない)になるっぽい
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
