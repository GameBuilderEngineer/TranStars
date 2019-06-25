#include "DynamicClass.h"
#include "Stage.h"

//クラス
ObjStr* DynamicClass::dynObjPop() {
	if (!getdynObjPopPossive()) return NULL;//確保できる領域が限界に達していたらそれ以上作らない

	if (v.size() > 1) {
		int i = rand() % v.size();
		if (v[i].m_use == false)//useがfalseなものにたまたま当たれば再利用
			return &v[i];
	}

	ObjStr o; v.push_back(o);
	return &v.back(); 
}

void DynamicClass::replaceVector() {
	for (ObjStr &i : v)
		deletexBased(&i);//x順リストから全削除

	for (std::vector<ObjStr>::iterator i = v.begin(); i != v.end();) {
		if (i->m_use == false)//useがfalseなものをvから消去
			i = v.erase(i);	//繰り返し中の要素削除によって総量が変わりイテレがずれるので、戻り値を受ける必要あり
		else
			i++;//eraseの戻り値は次の要素なので、それを受けた場合は++しなくてよい
	}

	if (v.capacity() - v.size() > RESIZE_VALUE)
		v.shrink_to_fit();//capacityをsizeまで減らす

	v.reserve(min(v.capacity() + RESIZE_VALUE, v.max_size()));//max_sizeを超えないようにcapacityを増やす

	for (ObjStr &i : v)
		setxBased(&i);//x順リストに再全登録

	int a = 0;
}
void DynamicClass::initialize() { v.reserve(RESIZE_VALUE);}
void DynamicClass::uninitialize() { v.clear(); }//動的オブジェクト全削除

void DynamicClass::update() {
	for (ObjStr &i : v) {//西川 この記法では&の付いた参照変数とやらで宣言しないと書換不能(iは書き換わるがvの中身は書き換わらない)になるっぽい
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
