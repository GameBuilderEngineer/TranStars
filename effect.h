#pragma once
#include "main.h"
#include "Image.h"

// エフェクトの

// タイプ
enum effTypes {
	eNO_TYPE = -1,
		ePARTICLE,//光の粒
		eLUMINE,//発光
		eSPLIT,//割れる
		eTAIL,//隕石の尾
		eMAGIC,//魔法陣
	eTYPE_MAX
};

// データ
typedef struct {
	effTypes m_type;					//エフェクトタイプ
	bool	 m_use;						//useフラグ

	D3DXVECTOR2	m_pos;					//座標
	float		m_rot;					//角度
	D3DXVECTOR2 m_scl;					//大きさ

	D3DXVECTOR2 m_speed;				//速度
	D3DXVECTOR2 m_accel;				//加速度

	int		m_time;						//経過時間
	int		m_tMAX;						//経過時間MAX
	short	m_mode;						//段階

	Image m_image;						//描画情報
}EffData;

// ノード
typedef struct __node_eff {
	EffData effD;
	struct __node_eff *prev;			// 前ノードへのポインタ
	struct __node_eff *next;			// 後ノードへのポインタ
}EffNode;

// 循環・重連結リスト
typedef struct {
	EffNode *head;						// 先頭(左端)ダミーノードへのポインタ
	EffNode *crnt;						// 着目ノードへのポインタ
}EffList;

void initializeEffect(EffList* eff);
void uninitializeEffect(EffList* eff);
void updateEffect(EffList* eff);
void drawEffect(EffList* eff);

void makeParticle(EffList* eff, D3DXVECTOR2 pos);
void makeMagic(EffList* eff, D3DXVECTOR2 pos);