//西川
#include "object.h"
#include "collision.h"
//#include "stdlib.h"//malloc用
#include"textureLoader.h"
#include "read_text.h"
#include "textDX.h"
#include "input.h"
#include "fileLoader.h"


//菅野
//改造しました。
//ステージ構造体とオブジェクト構造体の役割が、それぞれ混在していると判断したので、
//ファイル分けをしました。
//このオブジェクトcppは、基本的には、一つのオブジェクトに作用する関数、データで構成しました。

const float VALUE_ATTRACTION = 0.02f; // 引力の強さ
const float RANGE_ATTRACTION = 800.0f;	// 引力の働く範囲

//オブジェクトをセットする系ローカル関数
ObjStr cleanObj(int i);
Image cleanTex(void);

//オブジェクトを個別処理する関数
//機能ごとにファイル分けをした方が良いと思います。（kanno）
void updatePlayer(ObjStr* p_obj);
void setBlackHole(ObjStr* p_obj);
void updateBlackHole(ObjStr* p_obj);
void setWhiteHole(ObjStr* p_obj);
void updateWhiteHole(ObjStr* p_obj);
void resetStar(ObjStr* p_obj);
//いろいろ応用できそうな計算処理的関数
float objectLength(ObjStr* p_obj1, ObjStr* p_obj2);				//2つのオブジェクト間の距離を計算
D3DXVECTOR2 objectDirection(ObjStr* p_obj1, ObjStr* p_obj2);	// オブジェクト1に対するオブジェクト2の方向ベクトルを戻す


/*コリジョンリストに必要そうなもの
obID/obType/pos/rot/scl/coltype

アクションリスト

エフェクトリスト
*/


void initializeObject(ObjStr *obj,int id, int objType,VECTOR2 position,float angle){

	//p_stgobj->m_STAGE = stage;
	//Stage *p_fromstage = get_g_pStage(stage);//今から取得するステージ
	//p_stgobj->m_OBJNUM = p_fromstage->num_m_pObj + PLUS_OBJNUM;
	//for (int i = 0; i < p_stgobj->m_OBJNUM; i++) {
	//	if (NO_TYPE < i && i < FROMFILE_TYPE_MAX) {
	
	//↓ステージのテクスチャたちの初期値＝テクスチャリスト/実際には外からもらう値
	//for (int j = 0; j < TYPE_MAX; j++) {
	//	k = (objTypes)(j);
	//	if (NO_TYPE < k && k < TYPE_MAX/* && k != FROMFILE_TYPE_MAX*/) {
	//		StubTex[j].m_type = k;

	//菅野：2019/5/26改修

	//↓オブジェクトの初期値
	obj->m_type = (objTypes)objType;
	obj->m_id = id;
	obj->m_pos = position;
	obj->m_rot = angle;

	switch (obj->m_type) {
	case CHARA_PLAYER://星
		obj->m_use = true;
		obj->m_pos = D3DXVECTOR2{ 200.0f , 450.0f };
		obj->m_speed.x = -1.0f;
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::STAR1), obj->m_pos.x, obj->m_pos.y,50.0f,50.0f);
		break;
	case CHARA_BLACKHOLE://ブラックホール
		obj->m_use = true;
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::BLACK_HOLE), obj->m_pos.x, obj->m_pos.y, 80.0f, 80.0f);
		break;
	case CHARA_WHITEHOLE://ホワイトホール
		obj->m_use = true;
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::WHITE_HOLE), obj->m_pos.x, obj->m_pos.y, 80.0f, 80.0f);
		break;
	case CHARA_COMET://隕石
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::COMET), obj->m_pos.x, obj->m_pos.y, 100.0f, 100.0f);
		break;
	case CHARA_KEY://カギ
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::COMET), obj->m_pos.x, obj->m_pos.y, 100.0f, 100.0f);
		break;
	case CHARA_COIN://収集アイテム
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::COMET), obj->m_pos.x, obj->m_pos.y, 100.0f, 100.0f);
		break;
	case STAGE_HURDLE://動かせる障害物
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::COMET), obj->m_pos.x, obj->m_pos.y, 100.0f, 100.0f);
		break;
	case STAGE_WALL:			
		//動かせない壁　地面とか
		obj->m_use = true;
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::WALL), obj->m_pos.x, obj->m_pos.y, 40.0f, 300.0f);
		break;
	case UI_EFFECT:
		//エフェクト
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitAnimeImage(&obj->m_image, getTexture(textureLoaderNS::BACK_GROUND), obj->m_pos.x, obj->m_pos.y, 160.0f, 80.0f,3,5,10,5);
		break;
	case UI_CURSOR://西川0525
		//ブラックホール置くカーソル
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::MAGIC_CIRLE), obj->m_pos.x, obj->m_pos.y, 160.0f, 160.0f);
		break;
	case STAGE_LOCK:
		//鍵で開けられる扉
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::MAGIC_CIRLE), obj->m_pos.x, obj->m_pos.y, 160.0f, 160.0f);
		break;
	case EVENT_GOAL:
		//ゴール
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::MAGIC_CIRLE), obj->m_pos.x, obj->m_pos.y, 160.0f, 160.0f);
		break;
	case UI_HP:
		//残機表示
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		InitImage(&obj->m_image, getTexture(textureLoaderNS::MAGIC_CIRLE), obj->m_pos.x, obj->m_pos.y, 160.0f, 160.0f);
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
	if (obj->m_use == false) return;
	switch (obj->m_type) {//タイプごとに処理分け
	case CHARA_PLAYER:
		//星
		updatePlayer(obj->m_ptr);
		break;
	case CHARA_BLACKHOLE:
		//ブラックホール
		if (getMouseLButtonTrigger()) // 右クリックでセット
			setBlackHole(obj->m_ptr);
		updateBlackHole(obj->m_ptr);
		break;
	case CHARA_WHITEHOLE:
		//ホワイトホール
		if (getMouseRButtonTrigger()) // 右クリックでセット
			setWhiteHole(obj->m_ptr);
		updateWhiteHole(obj->m_ptr);
		break;
	case CHARA_COMET:
		//隕石
		break;
	case CHARA_KEY:
		//鍵
		break;
	case CHARA_COIN:
		//収集アイテム
		break;
	case STAGE_HURDLE:
		//動かせる障害物
		break;
	case STAGE_WALL:
		//動かせない壁　地面とか
		if (checkHitObjRR(obj->m_ptr, obj->m_ptr->m_tar))
		{
			resetStar(obj->m_ptr->m_tar);
		};
		break;
	case STAGE_LOCK:
		//鍵で開けられる扉
		break;
	case EVENT_GOAL:
		//ゴール
		break;
	case UI_CURSOR://西川 0525
		//ブラックホール置くカーソル
		if (getMouseLButtonTrigger() || getMouseRButtonTrigger()) {
			obj->m_pos = { (float)getMouseX() - 40.0f, (float)getMouseY() - 40.0f };
			obj->m_pos.y += obj->m_image.height;
			obj->m_image.height = 0.0f;

			setAngle(&obj->m_image, 0.0f);
		}
		if ((obj->m_image.height < obj->m_image.width)) {
			obj->m_pos.y -= (float)obj->m_image.width / 25.0f;
			obj->m_image.height += (float)obj->m_image.width / 25.0f;

			obj->m_image.angle -= 2.0f;//回転の相殺
		}
		else {
			obj->m_pos = { (float)getMouseX() - 40.0f, (float)getMouseY() - 40.0f };
			obj->m_image.height = obj->m_image.width;
		}
		break;
	case UI_EFFECT:
		//エフェクト
		break;
	case UI_HP:
		//残機表示
		break;
	}
}

void drawObject(ObjStr* obj){
	//全てのオブジェクトを描画　※これだと描画順をタイプごとに揃えたりできないので、描画用のリストを作ることになるのかも
	if (obj->m_use == false) return;
	setPosition(&(obj->m_image), obj->m_pos.x , obj->m_pos.y);
	setAngle(&(obj->m_image), obj->m_image.angle + 1);
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

ObjStr cleanObj(int i) {//Objをリセット
	return {
		NO_TYPE,
		short(i),
		false,
		NULL,
		NULL,
		{0.0f,0.0f},
		0.0f,
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		int(0),
		short(0),
		0.0f,
		{0.0f,0.0f}
//		cleanTex()
	};
}

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

void updateBlackHole(ObjStr* obj) {
	// 引力を計算する
	obj->m_attract = objectDirection(obj, obj->m_tar) * VALUE_ATTRACTION;
	if (obj->m_use == true)// ブラックホールが有効ならば
	{
		if (objectLength(obj, obj->m_tar) <= RANGE_ATTRACTION) // プレイヤーの距離が引力の働く範囲内ならば
			obj->m_tar->m_accel =
			obj->m_attract * (1-(objectLength(obj, obj->m_tar) / RANGE_ATTRACTION));	// プレイヤーの加速度へ引力を加算する
			// (引力) * (1 - プレイヤー距離/引力範囲)
	}
};

void updateWhiteHole(ObjStr* p_obj) {

};

void  setBlackHole(ObjStr* p_obj) {
	p_obj->m_use = true;
	p_obj->m_pos = D3DXVECTOR2{ (float)getMouseX(),(float)getMouseY() };
};

void  setWhiteHole(ObjStr* p_obj) {
	p_obj->m_pos = D3DXVECTOR2{ (float)getMouseX(),(float)getMouseY() };
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