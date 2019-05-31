#include "BlackHole.h"
#include "input.h"
#include "effect.h"
#include "stage.h"

void initializeBlackHole(ObjStr* blackHole, ObjStr* others,int targetNum)
{
	blackHole->m_use = false;
	blackHole->onAttract = false;
	blackHole->m_scl = { 1.0f,1.0f };
	blackHole->m_speed = { 0.0f,0.0f };
	blackHole->m_accel = { 0.0f,0.0f };
	blackHole->m_attract = { 0.0f,0.0f };
	blackHole->m_time = -1;
	blackHole->m_mode = -1;
	blackHole->m_rad = 50.0f;
	blackHole->m_rect = { 100.0f,100.0f };
	InitImage(&blackHole->m_image, getTexture(textureLoaderNS::BLACK_HOLE), blackHole->m_pos.x, blackHole->m_pos.y, 80.0f, 80.0f);
	//ブラックホールの影響を受けるオブジェクトをセットする
	blackHole->m_tar = others;
	blackHole->targetNum = targetNum;
}

void setBlackHole(ObjStr* blackHole) {
	blackHole->m_use = !blackHole->m_use;

	if (blackHole->m_use)
		makeMagic(getEffect(), { (float)getMouseX(), (float)getMouseY() });//西川0531 マウスの位置に魔法陣配置
	else
		makeMagic(getEffect(), blackHole->m_pos);//西川0531 BHがいた位置に魔法陣配置

	blackHole->m_pos = D3DXVECTOR2{
		(float)getMouseX() - blackHole->m_image.width / 2.0f,(float)getMouseY() - blackHole->m_image.height / 2.0f };
};

void updateBlackHole(ObjStr* blackHole) {
	if (getMouseLButtonTrigger()) // 左クリックでセット
		setBlackHole(blackHole);
	if (blackHole->m_use == false)return;
	// 引力を計算する
	for (int i = 0; i < blackHole->targetNum; i++) {
		if (!blackHole->m_tar[i].onAttract)continue;//引力影響を受けるか
		blackHole->m_attract = objectDirection(blackHole, &blackHole->m_tar[i]) * VALUE_ATTRACTION;
		if (objectLength(blackHole, &blackHole->m_tar[i]) <= RANGE_ATTRACTION) 
		{// オブジェクトの距離が引力の働く範囲内ならば
			// オブジェクトの加速度へ引力を加算する
			blackHole->m_tar[i].m_accel =
				blackHole->m_attract * (1 - (objectLength(blackHole, &blackHole->m_tar[i]) / RANGE_ATTRACTION));
				// (引力) * (1 - オブジェクト距離/引力範囲)
		}
	}
};

void sendObject(ObjStr* collisionObject,ObjStr* blackHole)
{
	collisionObject->m_pos = blackHole->whiteHole->m_pos;
}//西川