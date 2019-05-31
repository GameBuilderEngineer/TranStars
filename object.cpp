//西川
#include "object.h"
#include "collision.h"
//#include "stdlib.h"//malloc用
#include"textureLoader.h"
#include "read_text.h"
#include "textDX.h"
#include "input.h"
#include "fileLoader.h"
#include "SmallStar.h"
#include "BlackHole.h"
#include "WhiteHole.h"
#include "SmallStar.h"
#include "BigStar.h"
#include "comet.h"
#include "PopStar.h"
#include "Cursor.h"
#include "PopComet.h"
#include "BigStarFrame.h"
#include "SmallStarFrame.h"
#include "StarDust.h"
#include "StarLine.h"
#include "Reflection.h"

//菅野
//改造しました。
//ステージ構造体とオブジェクト構造体の役割が、それぞれ混在していると判断したので、
//ファイル分けをしました。
//このオブジェクトcppは、基本的には、一つのオブジェクトに作用する関数、データで構成しました。


//オブジェクトをセットする系ローカル関数
//ObjStr cleanObj(int i);
Image cleanTex(void);

//オブジェクトを個別処理する関数
//機能ごとにファイル分けをした方が良いと思います。（kanno）
void updatePlayer(ObjStr* p_obj);



void resetStar(ObjStr* p_obj);
//いろいろ応用できそうな計算処理的関数

/*コリジョンリストに必要そうなもの
obID/obType/pos/rot/scl/coltype

アクションリスト

エフェクトリスト
*/


void initializeObject(ObjStr *obj,int id, int objType,VECTOR2 position,float angle,ObjStr* others,int otherNum){
	//菅野：2019/5/26改修

	//↓オブジェクトの初期値
	obj->m_type = (objTypes)objType;
	obj->m_id = id;
	obj->m_pos = position;
	obj->m_rot = angle;

	switch (obj->m_type) {
	case CHARA_BLACKHOLE://ブラックホール
		initializeBlackHole(obj, others,otherNum);
		break;
	case CHARA_WHITEHOLE://ホワイトホール
		initializeWhiteHole(obj);
		break;
	case UI_CURSOR://西川0525
		//カーソル
		initializeCursor(obj);
		break;
	case CHARA_SMALL_STAR://星
		initializeSmallStar(obj);
		break;
	case CHARA_BIG_STAR://星
		initializeBigStar(obj);
		break;
	case CHARA_COMET://隕石
		initializeComet(obj);
		break;
	case POP_STAR://星がポップする場所
		initializePopStar(obj);
		break;
	case POP_COMET://隕石発生場所
		initializePopComet(obj);
		break;
	case CHARA_SMALL_STARFRAME://星（小）を嵌める型
		initializeSmallStarFrame(obj);
		break;
	case CHARA_BIG_STARFRAME://星（大）を嵌める型
		initializeBigStarFrame(obj);
		break;
	case CHARA_STARDUST://壁・星のくずの障害物
		initializeStarDust(obj);
		break;
	case STAGE_STARLINE://星と星を結ぶ線
		initializeStarLine(obj);
		break;
	case STAGE_REFLECTION://物体を反射する壁
		initializeReflection(obj);
		break;
	default:
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		obj->m_image.g_pD3DTexture = *getTexture(textureLoaderNS::BACK_GROUND);
		obj->m_image.width = 100.0f;
		obj->m_image.height = 100.0f;
		obj->m_image.playAnime = false;
		obj->m_image.ANIME_TIME = 1;
		obj->m_image.ANIME_PATTERN = 1;
		obj->m_image.DIVIDE_U = 1;
		obj->m_image.DIVIDE_V = 1;
		InitImage(&obj->m_image, getTexture(textureLoaderNS::MAGIC_CIRCLE), obj->m_pos.x, obj->m_pos.y, 160.0f, 160.0f);
		break;
	}
}

void uninitializeObject(ObjStr* obj) {
	if (obj != NULL) {
//		free(Obj);
		//delete[]obj;
		//obj = NULL;
		//誤ってfree/deleteを２連続でやるとヤバい かつ NULLぽがfree/deleteされる分には平気 らしいのでこうした
	}
	//while (ShowCursor(TRUE) != 0);//マウスを表示
}

void updateObject(ObjStr* obj) {
	switch (obj->m_type) {//タイプごとに処理分け
	case CHARA_BLACKHOLE:
		//ブラックホール
		updateBlackHole(obj);
		break;
	case CHARA_WHITEHOLE:
		//ホワイトホール
		updateWhiteHole(obj);
		break;
	case UI_CURSOR://西川 0525
		//ブラックホール置くカーソル
		updateCursor(obj);
		break;
	case CHARA_SMALL_STAR:
		//星（小）
		updateSmallStar(obj);
		break;
	case CHARA_BIG_STAR:
		//星（大）
		break;
	case CHARA_COMET:
		//隕石
		break;
	case POP_STAR:
		//星（小）が発生する場所
		break;
	case POP_COMET:
		//隕石が発生する場所
		break;
	case CHARA_SMALL_STARFRAME:
		//星（小）がはまる型
		break;
	case CHARA_BIG_STARFRAME:
		//星（大）がはまる型
		break;
	case CHARA_STARDUST:
		//星の壁
		break;
	case STAGE_STARLINE:
		//星と星を結ぶ線
		break;
	case STAGE_REFLECTION:
		//星と星を結ぶ線
		break;
	default:
		break;
	}
	//オブジェクトの基本処理
	if (obj->m_use == false)return;
	obj->m_pos += obj->m_accel;
	setPosition(&(obj->m_image), obj->m_pos.x , obj->m_pos.y);
	setAngle(&(obj->m_image), obj->m_image.angle);
}

void drawObject(ObjStr* obj){
	//全てのオブジェクトを描画　※これだと描画順をタイプごとに揃えたりできないので、描画用のリストを作ることになるのかも
	if (obj->m_use == false) return;
	DrawImage(&(obj->m_image));
}

void printObject(ObjStr* obj) {
	txtLineReset(int(obj->m_pos.y + obj->m_image.height));//自動改行位置をセット
	printTextDX(getDebugFont(), "type", int(obj->m_pos.x), txtLineBreak(), int(obj->m_type));
	printTextDX(getDebugFont(), "id", int(obj->m_pos.x), txtLineBreak(), obj->m_id);
	printTextDX(getDebugFont(), "x", int(obj->m_pos.x), txtLineBreak(), obj->m_pos.x);
	printTextDX(getDebugFont(), "y", int(obj->m_pos.x), txtLineBreak(), obj->m_pos.y);

	/*************************************************
	printTextDX(getDebugFont(), "Length",0, 90, objectLength(&p_stgobj->m_Obj[plID],&p_stgobj->m_Obj[bhID]));
	printTextDX(getDebugFont(), "BH_att.x", 0, 120, p_stgobj->m_Obj[bhID].m_attract.x);
	printTextDX(getDebugFont(), "BH_att.y", 0, 150, p_stgobj->m_Obj[bhID].m_attract.y);
	printTextDX(getDebugFont(), "PL_speed.x", 0, 180, p_stgobj->m_Obj[plID].m_speed.x);
	printTextDX(getDebugFont(), "PL_speed.y", 0, 210, p_stgobj->m_Obj[plID].m_speed.y);
	printTextDX(getDebugFont(), "PL_accel.x", 0, 240, p_stgobj->m_Obj[plID].m_accel.x);
	printTextDX(getDebugFont(), "PL_accel.y", 0, 270, p_stgobj->m_Obj[plID].m_accel.y);
	****************************************************/

	//プレイヤーIDを検索して使用
	//D3DXVECTOR2 center = computeRotatedBox(&obj[plID]);
	//printTextDX(getDebugFont(), "PL_corner.左上x", 0, 90,  obj[plID].m_corner[0].x);
	//printTextDX(getDebugFont(), "PL_corner.左上y", 0, 120, obj[plID].m_corner[0].y);
	//printTextDX(getDebugFont(), "PL_corner.右上x", 0, 150, obj[plID].m_corner[1].x);
	//printTextDX(getDebugFont(), "PL_corner.右上y", 0, 180, obj[plID].m_corner[1].y);
	//printTextDX(getDebugFont(), "PL_corner.左下x", 0, 210, obj[plID].m_corner[2].x);
	//printTextDX(getDebugFont(), "PL_corner.左下y", 0, 240, obj[plID].m_corner[2].y);
	//printTextDX(getDebugFont(), "PL_corner.右下x", 0, 270, obj[plID].m_corner[3].x);
	//printTextDX(getDebugFont(), "PL_corner.右下y", 0, 300, obj[plID].m_corner[3].y);

	//printTextDX(getDebugFont(), "PL_center.x", 0, 330, center.x);
	//printTextDX(getDebugFont(), "PL_center.y", 0, 360, center.y);

}

float getObjectSizeLonger(ObjStr* obj) {
	float dgnl = sqrtf((obj->m_rect.x * obj->m_rect.x +
		obj->m_rect.y * obj->m_rect.y)) / 2.0f;
	if (dgnl >= obj->m_rad) return dgnl;
	else return obj->m_rad;
}//西川0519  オブジェクトの持つメンバのうち、矩形の対角線と半径で長い方を返す


/////以下オブジェクトセット系ローカル関数

//ObjStr cleanObj(int i) {//Objをリセット
//	return {
//		NO_TYPE,
//		short(i),
//		false,
//		NULL,
//		NULL,
//		{0.0f,0.0f},
//		0.0f,
//		{0.0f,0.0f},
//		{0.0f,0.0f},
//		{0.0f,0.0f},
//		{0.0f,0.0f},
//		int(0),
//		short(0),
//		0.0f,
//		{0.0f,0.0f}
////		cleanTex()
//	};
//}

Image cleanTex(void) {//Texをリセット
	Image nullTex;
	InitImage(&nullTex, getTexture(textureLoaderNS::TEXTURE_NUMBER(0)), 0, 0, 1, 1);
	return nullTex;
}

//void setObjFromFile(ObjStr *obj, int i, Stage* p_fromstage){
//	//もらったステージデータの中からオブジェクトをセット
//
//	if (StubObj->m_type != NO_TYPE) {//ステージデータから中身を直接もらえばいいもの
//		obj->m_type = StubObj->m_type;
//		obj->m_id = StubObj->m_id;
//		obj->m_use = false;
//		obj->m_ptr = obj;
//		obj->m_tar = NULL;
//
//		obj->m_pos = StubObj->m_pos;
//		obj->m_rot = StubObj->m_rot;
//		obj->m_scl = StubObj->m_scl;
//
//		obj->m_speed = D3DXVECTOR2{0.0f,0.0f};
//		obj->m_accel = StubObj->m_accel;
//		obj->m_attract = StubObj->m_attract;
//
//		obj->m_time = StubObj->m_time;
//		obj->m_mode = StubObj->m_mode;
//
//		obj->m_rad = StubObj->m_rad;
//		obj->m_rect = StubObj->m_rect;
//		obj->m_rect = { StubTex->width,StubTex->height };
//	}
//	else {//ステージデータが空のタイプになっていたら
//		*obj = cleanObj(i);
//	}
//}

//void setObjNotFrom(ObjStr *obj, int i, int objnum) {
	//UIなど、ステージごとに変わらないのでファイルに保存する必要もなく、毎回こちらで設定すればいいオブジェクトをセット
	//obj->m_id = i;
	//obj->m_use = true;
	//switch (i - objnum) {
	//case 0:
	//	obj->m_type = UI_CURSOR;
	//	//西川0525
	//	obj->m_rect = { StubTex[int(UI_CURSOR)].width,StubTex[int(UI_CURSOR)].height };//西川0525
	//	break;
	//case 1:
	//	obj->m_type = UI_EFFECT;
	//	obj->m_pos = { 720.0f,480.0f };
	//	break;
	//default:
	//	obj->m_type = UI_HP;
	//	obj->m_pos = { 0.0f,0.0f };
	//	break;
	//}
//}

//void setObjTex(ObjStr* obj, int i) {//ObjにStubTexの中身をセット
//	if (obj->m_type != NO_TYPE) {
//		//StubTexture *p_tex = &(StubTex[int(obj->m_type)]);
//		if (p_tex->m_type != NO_TYPE) {
//			if (obj->m_image.playAnime == false) {//静止画だったら
//				InitImage(&(obj->m_image), getTexture(StubTex[int(obj->m_type)].texture), obj->m_pos.x, obj->m_pos.y,
//					p_tex->width, p_tex->height);
//			}
//			else {//アニメだったら
//				InitAnimeImage(&(obj->m_image), getTexture(StubTex[int(obj->m_type)].texture), obj->m_pos.x, obj->m_pos.y,
//					p_tex->width, p_tex->height,
//					p_tex->ANIME_TIME, p_tex->ANIME_PATTERN, p_tex->DIVIDE_U, p_tex->DIVIDE_V);
//			}
//		}
//		else {//テクスチャデータが空のタイプになっていたら
//			obj->m_image = cleanTex();
//		}
//	}
//	else {//オブジェクトデータが空のタイプになっていたら
//		obj->m_image = cleanTex();
//	}
//}

void updatePlayer(ObjStr* obj) {
	//p_obj->m_rot = D3DX_PI / 4;
	obj->m_speed.x += obj->m_accel.x;	// 加速度を速度へ加算する
	obj->m_speed.y += obj->m_accel.y;	// 加速度を速度へ加算する

	if (obj->m_speed.x > 2.0f)
	{
		obj->m_speed.x = 2.0f;
	}
	if (obj->m_speed.y > 2.0f)
	{
		obj->m_speed.y = 2.0f;
	}

	if (obj->m_speed.x < -2.0f)
	{
		obj->m_speed.x = -2.0f;
	}
	if (obj->m_speed.y < -2.0f)
	{
		obj->m_speed.y = -2.0f;
	}

	//p_obj->m_pos.x += p_obj->m_speed.x;			// 位置情報を速度で更新
	//p_obj->m_pos.y += p_obj->m_speed.y;			// 位置情報を速度で更新

};




// 2つのオブジェクト間の距離を(算出する/戻す/返す)
float objectLength(ObjStr* p_obj1, ObjStr* p_obj2)
{
	D3DXVECTOR2 toTarget;
	toTarget.x = p_obj1->m_pos.x - p_obj2->m_pos.x;
	toTarget.y = p_obj1->m_pos.y - p_obj2->m_pos.y;
	float length = D3DXVec2Length(&toTarget);
	return length;
};

// オブジェクト1に対するオブジェクト2の方向ベクトルを戻す
D3DXVECTOR2 objectDirection(ObjStr* p_obj1, ObjStr* p_obj2)
{
	D3DXVECTOR2 dir;
	dir.x = p_obj1->m_pos.x - p_obj2->m_pos.x;
	dir.y = p_obj1->m_pos.y - p_obj2->m_pos.y;
	// 正規化して大きさを1にする
	D3DXVec2Normalize(&dir, &dir);
	return dir;
}

void resetStar(ObjStr* p_obj)
{
	p_obj->m_pos = D3DXVECTOR2{ WINDOW_WIDTH , 450.0f };
	p_obj->m_speed = D3DXVECTOR2{ -1.0f,0.0f };
	p_obj->m_accel = D3DXVECTOR2{ 0.0f,0.0f };
}
void setWhiteHole(ObjStr* obj, ObjStr* whiteHole)
{ obj->whiteHole = whiteHole; }