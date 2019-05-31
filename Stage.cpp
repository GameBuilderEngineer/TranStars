//stageシーン
#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include "textureLoader.h"
#include "object.h"
#include "Select.h"
#include "effect.h"//西川0525 エフェクト
#include "useList.h"//西川0530
#include "collision.h"//西川0530 コリジョン内の関数をリストに渡すため
#include "StageClass.h"
#include "BlackHole.h"
#include "Select.h"
#include "action.h"

StageClass stage;//ステージ別データ

Image gameBG;
TF_List typeCollisionList;//西川0530 コリジョン用 タイプ関係と実行する関数のリスト(initializeで作ってゲーム中通用)
TF_List typeActionList;//西川0530 アクション用 タイプリスト(通用)
DataList xBasedList;//西川0518 x座標順 オブジェクトリスト(通用)
DataList resultList;//西川0518 確かめ結果 オブジェクト関係リスト(updateで毎フレーム作って使い捨て)
EffList effectList;//西川0525 エフェクト一つ一つが入ったリスト(通用)

ObjStr blackHole;//ブラックホール
ObjStr whiteHole;//ホワイトホール
ObjStr cursor;//カーソル
ObjStr* star = NULL;//星へのポインタ[]動的配列用
ObjStr* comet = NULL;//隕石へのポインタ[]動的配列用

void setTFLists();

void initializeStage() {
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
	initializeObjList(&xBasedList, &resultList);//西川0527
	initializeTypeFuncList(&typeCollisionList);
	initializeTypeFuncList(&typeActionList);
	initializeEffect(&effectList);//西川0527

	setTFLists();//西川0531
};

void startStage() {	
	//ステージセレクトで、ステージ変数から初期化するようにする:とりあえずステージ１
	stage.initialize(getSelectStage());//菅野
	initializeObject(&whiteHole, 10000, CHARA_WHITEHOLE, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
	initializeObject(&blackHole, 10000, CHARA_BLACKHOLE, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
	initializeObject(&cursor, 10000, UI_CURSOR, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());

	setWhiteHole(&blackHole, &whiteHole);

	//initializeObject(&cursor, 10000, UI_CURSOR, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
	//initializeObject(&cursor, 10000, UI_CURSOR, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());

	startEffect(&effectList);//西川0527
	startObjList(&stage, &xBasedList, &resultList);//西川0527

	setObjEdge(&xBasedList, &blackHole);

};//西川0518 新しいステージに入る前に呼ぶ関数

void updateStage() {
	clearResultList(&resultList);//	前フレームの結果リストを廃棄

	// 樋沼追加
	// timerはmainにあるから、そこでif文するか、ここにtimerを持ってくるかどちらがいいか
	// ↑新たにTimerクラスのインスタンスを作成すると良いと思います。

	// 大体ここまで
	stage.update();//菅野
	updateObject(&whiteHole);
	updateObject(&blackHole);
	updateObject(&cursor);
	
//	if (getMouseLButtonTrigger())
//		makeParticle(&effectList, { (float)getMouseX(), (float)getMouseY() });//西川0525
//	if (getMouseRButtonTrigger())
//		makeMagic(&effectList, { (float)getMouseX(), (float)getMouseY() });//西川0526
//		makeSplit(&effectList, { (float)getMouseX(), (float)getMouseY() }, stage.getObj()[0].m_image);//西川0527
//	makeEffect(&effectList, eTAIL, &stage.getObj()[3]);//西川0528
	updateEffect(&effectList);//西川0525

	makeResultList(&typeCollisionList, &xBasedList, &resultList);//西川0527 x順リストを更新、同時進行的にコリジョン関数の入ったタイプリストを渡して結果リスト取得
	checkResultList(&typeActionList, &resultList,&effectList);//西川0530
};

void drawStage() {
	DrawImage(&gameBG);
	drawEffect(&effectList);//西川0530オブジェクトより先に描画

	stage.draw();//菅野
	drawObject(&whiteHole);
	drawObject(&blackHole);
	drawObject(&cursor);

};

void printStage() {
#ifdef _DEBUG
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "マウス中ボタンを押下で入力ダイアログボックスを表示する", 500, 30);
	printTextDX(getDebugFont(), "mX:", 1100, 0, getMouseX());
	printTextDX(getDebugFont(), "mY:", 1100, 30, getMouseY());

	if (GetKeyboardPress(DIK_LCONTROL)/*左CTRL*/) printList(&xBasedList);//西川0518 x順リストの中身を視覚化
	if (GetKeyboardPress(DIK_M)/*右CTRL*/) printList(&resultList);//西川0518 結果リストの中身を視覚化
	stage.print();//菅野
	printObject(&whiteHole);
	printObject(&blackHole);
	printObject(&cursor);
#endif
};

void unInitializeStage() {
	stage.uninitialize();//菅野//西川0527
	uninitializeEffect(&effectList);//西川0527
	uninitializeObjList(&xBasedList, &resultList);//西川0527
	uninitializeTypeFuncList(&typeCollisionList);//西川0530
	uninitializeTypeFuncList(&typeActionList);//西川0530
};

void finishStage() {
	finishEffect(&effectList);//西川0527
	finishObjList(&xBasedList, &resultList);//西川0527
};//西川0518 今のステージをやめた後に呼ぶ関数

void setTFLists() {
	setCollisionsList(&typeCollisionList, NO_TYPE, TYPE_MAX, NO_TYPE, TYPE_MAX, &checkHitObjRR);//重複があるが、これでよい
	setActionsList(&typeActionList, CHARA_SMALL_STAR, CHARA_COMET, CHARA_BLACKHOLE, CHARA_BLACKHOLE, &sendObject);
	setActionsList(&typeActionList, CHARA_SMALL_STAR, CHARA_COMET, STAGE_REFLECTION, STAGE_REFLECTION, &actReflect);
	setActionList(&typeActionList, CHARA_SMALL_STAR, CHARA_WHITEHOLE, &actSplit);
	setActionList(&typeActionList, CHARA_SMALL_STAR, CHARA_WHITEHOLE, &actSplit);

	optimizeActionList(&typeActionList);//同じタイプで同じ処理があれば削除
}
