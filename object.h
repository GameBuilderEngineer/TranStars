//西川
#pragma once

#include "main.h"
#include "Image.h"
enum objTypes{
	NO_TYPE = -1,
		CHARA_PLAYER,
		CHARA_BLACKHOLE,
		CHARA_WHITEHOLE,
		CHARA_COMET,
		CHARA_KEY,
		CHARA_COIN,
		STAGE_HURDLE,
		STAGE_WALL,
		STAGE_LOCK,
		EVENT_GOAL,
//	FROMFILE_TYPE_MAX,//西川0525
		UI_CURSOR,
		UI_EFFECT,
		UI_HP,
	TYPE_MAX,
	FROMFILE_TYPE_MAX = UI_CURSOR//西川0525
};

//shortは-0.5±32767.5、intは-0.5±2147483647.5←うんち

//************************************************************************
//オブジェクトの一つ一つ
// とりあえずメンバ変数は暫定。必要に応じて増やしたり減らしたりするかも。
// その場合は関連項目(関数とか)修正してくれるとありがたい。
//************************************************************************
typedef struct _obj{
	objTypes m_type;					//オブジェクトタイプ
	short	 m_id;						//全タイプが入っている配列内の、自分の番号
	bool	 m_use;						//useフラグ
	_obj*	 m_ptr;						//自身へのポインタ
	_obj*	 m_tar;						//ターゲットのポインタ(基本はブラックホール)

	D3DXVECTOR2	m_pos;					//座標
	float		m_rot;					//角度
	D3DXVECTOR2 m_scl;					//大きさ

	D3DXVECTOR2 m_speed;				//速度
	D3DXVECTOR2 m_accel;				//加速度(他のオブジェクトから及ぼされる力、慣性とか)
	D3DXVECTOR2 m_attract;				//引力　(自分以外のオブジェクトに及ぼす力とか)

	int		m_time;						//プレイヤーとは独立して勝手に動くオブジェクトがあれば使う(ステージギミック系)
	short	m_mode;						//同上、行動パターンとかはこっち

	float m_rad;						//半径(プレイヤーの当たり判定とか)
	D3DXVECTOR2 m_rect;					//矩形の辺長(ステージの当たり判定とか)
	D3DXVECTOR2	m_corner[4];			// 衝突ボックスの各頂点に対するベクトル

	//衝突以外でも使うなら配列になるかも(近寄ると動き出すとか、ブラックホールが吸い寄せ始める範囲とか)

	Image m_image;						//描画情報
}ObjStr;//Structure



#define STUB_OBJNUM (100)	//ステージのデータ内にあるオブジェクトの総数/実際には外からもらう値
#define PLUS_OBJNUM (5)		//ステージ側で保存する必要のないオブジェクト情報(UIなど)があればそれの数


void initializeObject(ObjStr *obj, int id, int objType, VECTOR2 position, float angle);
void uninitializeObject(ObjStr* obj);
void updateObject(ObjStr* obj);
void drawObject(ObjStr* obj);
void printObject(ObjStr* obj);

//西川0519  オブジェクトの持つメンバのうち、矩形の対角線と半径で長い方を返す
float getObjectSizeLonger(ObjStr* obj);
