//stageシーン
#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include "textureLoader.h"
#include "object.h"
#include "Select_Game.h" // 樋沼追加
#include "useList.h"//西川0518
#include "collision.h"//西川0518 コリジョン内の関数をリストに渡すため
#include "effect.h"//西川0525 エフェクト
#include "StageClass.h"

StageClass stage;//ステージ別データ

Image gameBG;
DataList xBasedList;//西川0518 x座標順・オブジェクト・リスト(initializeで作ってゲーム中通用)
DataList resultList;//西川0518 確かめ結果・オブジェクト関係・リスト(updateで毎フレーム作って使い捨て)
DataList typeList_col;//西川0525 タイプ相性リスト、衝突用(initializeで作ってゲーム中通用)
EffList effectList;//西川0525 エフェクト一つ一つが入ったリスト(initializeで作ってゲーム中通用)

void initializeStage() {
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};

void startStage() {
	
	//ステージセレクトで、ステージ変数から初期化するようにする:とりあえずステージ１
	stage.initialize(stageNS::STAGE01);//菅野
	initializeEffect(&effectList);//西川0525
	initializeObjList(&stage, &xBasedList, &resultList);


};//西川0518 新しいステージに入る前に呼ぶ関数

void updateStage() {
	// 樋沼追加
	// timerはmainにあるから、そこでif文するか、ここにtimerを持ってくるかどちらがいいか
	// ↑新たにTimerクラスのインスタンスを作成すると良いと思います。

	bool p_pause = *getPause();
	updatePause();
	// 大体ここまで
	stage.update();//菅野
	if (getMouseLButtonTrigger() || getMouseRButtonTrigger())
		makeParticle(&effectList, { (float)getMouseX() + 40.0f, (float)getMouseY() + 40.0f });//西川0525
	updateEffect(&effectList);//西川0525

	updateObjList(&xBasedList, &resultList, checkHitObjRR);//西川0518 x順リストを更新、同時進行的にコリジョン関数を渡してその結果リストを取得
//	cutResultList(&resultList, checkTypeComp_A);//西川0525
};

void drawStage() {
	DrawImage(&gameBG);
	stage.draw();//菅野
	drawEffect(&effectList);//西川0525
	drawPause(); // 樋沼
};

void printStage() {
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "マウス中ボタンを押下で入力ダイアログボックスを表示する", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());

	if (GetKeyboardPress(DIK_LCONTROL)/*左CTRL*/) printList(&xBasedList);//西川0518 x順リストの中身を視覚化
	if (GetKeyboardPress(DIK_M)/*右CTRL*/) printList(&resultList);//西川0518 結果リストの中身を視覚化
	stage.print();//菅野
};

void unInitializeStage() {
	finishStage();//西川0518
};

void finishStage() {
	stage.uninitialize();//菅野
	uninitializeEffect(&effectList);//西川0525
	uninitializeObjList(&xBasedList, &resultList);
};//西川0518 今のステージをやめた後に呼ぶ関数