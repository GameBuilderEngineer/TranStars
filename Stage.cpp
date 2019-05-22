#include "Stage.h"
#include "textDX.h"
#include "input.h"
#include "Image.h"
#include"textureLoader.h"
#include "messageDialog.h"
#include "inputDialog.h"
#include "object.h"
#include "Select_Game.h" // 樋沼追加
#include "useList.h"//西川0518
#include "collision.h"//西川0518 コリジョン内の関数をリストに渡すため

MessageDialog mDialog;
InputDialog inDialog;

StageObj stageObj;//西川 0.02
Image gameBG;
DataList xBasedList;//西川0518 x座標順・オブジェクト・リスト(ゲーム中通用)
DataList resultList;//西川0518 確かめ結果・オブジェクト関係・リスト(毎フレーム使い捨て)

void initializeStage() {
	inDialog.initialize(getHWnd());
	mDialog.initialize(getHWnd());
	mDialog.print("Hello World");
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
};
void startStage() {
	initializeObject(&stageObj, 0);//西川 0.02 ひとまず0ステージで
	initializeObjList(&stageObj, &xBasedList, &resultList);
};//西川0518 新しいステージに入る前に呼ぶ関数
void updateStage() {
	// 樋沼追加
	// timerはmainにあるから、そこでif文するか、ここにtimerを持ってくるかどちらがいいか
	bool p_pause = *getPause();
	updatePause();
	// 大体ここまで
	inDialog.update();
	mDialog.update();
	updateObject(&stageObj);
	updateObjList(&xBasedList, &resultList, checkHitObjRR);//西川0518 x順リストを更新、同時進行的にコリジョン関数を渡してその結果リストを取得
	check_updateAndResultList(&resultList, checkHitObjCC);//西川0518
	if (getMouseMButton())
	{
		inDialog.print("please InputText");
	}

};
void drawStage() {
	DrawImage(&gameBG);
	inDialog.draw();
	//mDialog.draw();
	drawObject(&stageObj);
	drawPause(); // 樋沼

};

void printStage() {
	printTextDX(getDebugFont(), "Stage", 0, 0);
	printTextDX(getDebugFont(), "マウス中ボタンを押下で入力ダイアログボックスを表示する", 500, 30);
	printTextDX(getDebugFont(), "mouseX:", 1000, 0, getMouseX());
	printTextDX(getDebugFont(), "mouseY:", 1000, 30, getMouseY());

	if (GetKeyboardPress(DIK_LCONTROL)/*左CTRL*/) printList(&xBasedList);//西川0518 x順リストの中身を視覚化
	if (GetKeyboardPress(DIK_RCONTROL)/*右CTRL*/) printList(&resultList);//西川0518 結果リストの中身を視覚化
	printObject(&stageObj);//西川 0.22
};
void unInitializeStage() {
	finishStage();//西川0518
};
void finishStage() {
	uninitializeObject(&stageObj);
	uninitializeObjList(&xBasedList, &resultList);
};//西川0518 今のステージをやめた後に呼ぶ関数
