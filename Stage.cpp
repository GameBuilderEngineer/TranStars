//stageシーン
#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include "textureLoader.h"
#include "object.h"
#include "Select_Game.h" // 樋沼追加
#include "useList.h"//西川0518
//#include "collision.h"//西川0518 コリジョン内の関数をリストに渡すため
#include "effect.h"//西川0525 エフェクト
#include "StageClass.h"

StageClass stage;//ステージ別データ

Image gameBG;
DataList typeCompatList;//西川0527 タイプ関係と実行する関数のリスト
DataList xBasedList;//西川0518 x座標順・オブジェクト・リスト(initializeで作ってゲーム中通用)
DataList resultList;//西川0518 確かめ結果・オブジェクト関係・リスト(updateで毎フレーム作って使い捨て)
EffList effectList;//西川0525 エフェクト一つ一つが入ったリスト(initializeで作ってゲーム中通用)

void initializeStage() {
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
	initializeObjList(&typeCompatList, &xBasedList, &resultList);//西川0527
	initializeEffect(&effectList);//西川0527
};

void startStage() {	
	//ステージセレクトで、ステージ変数から初期化するようにする:とりあえずステージ１
	stage.initialize(stageNS::STAGE01);//菅野
	startEffect(&effectList);//西川0527
	startObjList(&stage, &typeCompatList, &xBasedList, &resultList);//西川0527

};//西川0518 新しいステージに入る前に呼ぶ関数

void updateStage() {
	// 樋沼追加
	// timerはmainにあるから、そこでif文するか、ここにtimerを持ってくるかどちらがいいか
	// ↑新たにTimerクラスのインスタンスを作成すると良いと思います。

	bool p_pause = *getPause();
	updatePause();
	// 大体ここまで
	stage.update();//菅野
	if (getMouseLButtonTrigger())
		makeParticle(&effectList, { (float)getMouseX(), (float)getMouseY() });//西川0525
	if (getMouseRButtonTrigger())
//		makeMagic(&effectList, { (float)getMouseX(), (float)getMouseY() });//西川0526
		makeSplit(&effectList, { (float)getMouseX(), (float)getMouseY() }, &stage.getObj()[0].m_image);//西川0527
	makeTail(&effectList, { stage.getObj()[0].m_pos.x + stage.getObj()[0].m_image.width / 2.0f,
		stage.getObj()[0].m_pos.y + stage.getObj()[0].m_image.height / 2.0f }, stage.getObj()[0].m_speed);//西川0528
	updateEffect(&effectList);//西川0525

	updateObjList(&typeCompatList, &xBasedList, &resultList);//西川0527 x順リストを更新、同時進行的にコリジョン関数を渡してその結果リストを取得
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
	printTextDX(getDebugFont(), "mX:", 1100, 0, getMouseX());
	printTextDX(getDebugFont(), "mY:", 1100, 30, getMouseY());

	if (GetKeyboardPress(DIK_LCONTROL)/*左CTRL*/) printList(&xBasedList);//西川0518 x順リストの中身を視覚化
	if (GetKeyboardPress(DIK_M)/*右CTRL*/) printList(&resultList);//西川0518 結果リストの中身を視覚化
	stage.print();//菅野
};

void unInitializeStage() {
	stage.uninitialize();//菅野//西川0527
	uninitializeEffect(&effectList);//西川0527
	uninitializeObjList(&typeCompatList, &xBasedList, &resultList);//西川0527
};

void finishStage() {
	finishEffect(&effectList);//西川0527
	finishObjList(&typeCompatList, &xBasedList, &resultList);//西川0527
};//西川0518 今のステージをやめた後に呼ぶ関数