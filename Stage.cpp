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
//ObjStr cursor;//カーソル
DynamicClass comet;//隕石
DynamicClass star;//隕石

void setTFLists();

void initializeStage() {
	InitImage(&gameBG, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);
	initializeObjList(&xBasedList);//西川0604
	initializeObjList(&resultList);//西川0604
	initializeTypeFuncList(&typeCollisionList);
	initializeTypeFuncList(&typeActionList);
	initializeEffect(&effectList);//西川0527

	setTFLists();//西川0531
};

void startStage() {	
	//ステージセレクトで、ステージ変数から初期化するようにする:とりあえずステージ１
	stage.initialize(getSelectStage());//菅野
	comet.initialize();
	initializeObject(&whiteHole, 10000, CHARA_WHITEHOLE, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
	initializeObject(&blackHole, 10000, CHARA_BLACKHOLE, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());
//	initializeObject(&cursor, 10000, UI_CURSOR, D3DXVECTOR2(0,0), 0, stage.getObj(), stage.getObjNum());

	setWhiteHole(&blackHole, &whiteHole);

	startEffect(&effectList);//西川0527
//	startObjList(&stage, &xBasedList, &resultList);//西川0604initializeObjectの中に入れた

//	setxBased(&blackHole);//西川0604initializeObjectの中に入れた

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
	comet.update();
//	updateObject(&cursor);

	updateEffect(&effectList);//西川0525

	makeResultList(&typeCollisionList, &xBasedList, &resultList);//西川0527 x順リストを更新、同時進行的にコリジョン関数の入ったタイプリストを渡して結果リスト取得
	checkResultList(&typeActionList, &resultList,&effectList);//西川0530
};

void drawStage() {
	DrawImage(&gameBG);
	drawEffect(&effectList);//西川0530オブジェクトより先に描画

//	for (int i = 0; i < 1000; i++)//西川0602 わざとFPS下げる用
	stage.draw();//菅野
	drawObject(&whiteHole);
	drawObject(&blackHole);
	comet.draw();
//	drawObject(&cursor);

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
//	printObject(&cursor);
	comet.print();
#endif
};

void unInitializeStage() {
	stage.uninitialize();//菅野//西川0527
	uninitializeEffect(&effectList);//西川0527
	uninitializeObjList(&xBasedList); uninitializeObjList(&resultList);
	uninitializeTypeFuncList(&typeCollisionList);//西川0530
	uninitializeTypeFuncList(&typeActionList);//西川0530
};

void finishStage() {
	comet.uninitialize();
	finishEffect(&effectList);//西川0527
	finishObjList(&xBasedList); finishObjList(&resultList);
};//西川0518 今のステージをやめた後に呼ぶ関数
void setxBased(ObjStr* obj) {
	setObjEdge(&xBasedList, obj);
}
void deletexBased(ObjStr* obj) {
	deleteObjEdge(&xBasedList, obj);
}

EffList* getEffect() {
	return &effectList;
}
StageClass* getStageClass() {
	return &stage;
}
DynamicClass* getCometClass() {
	return &comet;
}
DynamicClass* getStarClass() {
	return &star;
}
void setTFLists() {
	//コリジョン
	setCollisionsList(&typeCollisionList, NO_TYPE, TYPE_MAX, NO_TYPE, TYPE_MAX, &checkHitObjRR);//重複があるが、これでよい

	//アクション
	setActionsList(&typeActionList, CHARA_SMALL_STAR, CHARA_COMET, CHARA_BLACKHOLE,
		CHARA_BLACKHOLE, &sendObject);//ブラックホールに当たったらホワイトホールに飛ぶか消滅

	setActionsList(&typeActionList, CHARA_SMALL_STAR, CHARA_COMET, STAGE_REFLECTION,
		STAGE_REFLECTION, &actReflect);//反射する

	setActionsList(&typeActionList, CHARA_SMALL_STAR, CHARA_COMET, 
		CHARA_STARDUST, CHARA_STARDUST, &actSplit);//星が割れる

	setActionList(&typeActionList, CHARA_SMALL_STAR, CHARA_SMALL_STARFRAME, &actFitSmallStar);//はまる
	setActionList(&typeActionList, CHARA_BIG_STAR, CHARA_BIG_STARFRAME, &actFitBigStar);//はまる

	optimizeActionList(&typeActionList);//同じタイプと同じ処理の組み合わせがあれば削除
}
