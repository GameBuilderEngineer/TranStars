// 樋沼追加

#ifndef _SELECT_GAME_H_
#define _SELECT_GAME_H_

#include "main.h"

namespace titleNS
{
	const float LOGO_WIDTH = 500;
	const float LOGO_HEIGHT = 500;
	const float PRESS_ENTER_WIDTH = 1368 / 4;
	const float PRESS_ENTER_HEIGHT = 201 / 4;
	const float NEW_GAME_WIDTH = 1336 / 5;
	const float NEW_GAME_HEIGHT = 331 / 5;
	const float CHOOSE_STAGE_WIDTH = 2247 / 5;
	const float CHOOSE_STAGE_HEIGHT = 331 / 5;
	const float CURSOR_SELECT_WIDTH = 1140 / 15;
	const float CURSOR_SELECT_HEIGHT = 1317 / 15;
	const float CURSOR_CHOOSE_WIDTH = 1140 / 30;
	const float CURSOR_CHOOSE_HEIGHT = 1317 / 30;
	const float THUM_STAGE_WIDTH = 200;
	const float THUM_STAGE_HEIGHT = 100;
	const float PAUSE_WIDTH = 1600 / 30;
	const float PAUSE_HEIGHT = 573 / 30;

	// Cursor位置の調整
	const float CURSOR_SELECT_FIX_X = 200;
	const float CURSOR_SELECT_FIX_Y = 0;
	const float CURSOR_CHOOSE_FIX_X = 50;
	const float CURSOR_CHOOSE_FIX_Y = 30;
}

enum MOVE_CURSOR_SELECT
{
	MOVE_NEW_GAME = 0,
	MOVE_CHOOSE_STAGE,
	MOVE_MAX
};

enum MOVE_CURSOR_CHOOSE
{
	STAGE01 = 0,
	STAGE02,
	STAGE03,
	STAGE04,
	STAGE05,
	STAGE06,
	STAGE07,
	STAGE08,
	STAGE09,
	MOVE_CHOOSE_MAX
};


// Title.cppに直接組み込む用の関数 
// updateとdrawはSwitchの処理だけ
void initSelectTitle();
void updateSelectTitle();
void drawSelectTitle();
void printSelectTitle();

// モード選択
// draw or update SelectTitle();内に組み込む関数（具体的な処理）
void moveSelectModeCursor();
int moveTitleCursor(int scene);

// ステージ選択
// draw or update SelectTitle();内に組み込む関数（具体的な処理）
void moveChooseStageCursor();
int moveStageCursor(int scene);
void fixCursorNum(); // Cursorの数字が0以下のときは最大値にする

// その他（モード・ステージ選択共用の関数）
void returnBeforeScene(); // 前の項目に戻る
void unInitializeSelectTitle(); // 終了処理
void changeCursorSize(); // Cursorのサイズをシーンごとに変える
void moveCursorPos(Image* image); // Cursorの位置を変える

// draw関数まとめ
void drawTitleStart();
void drawSelectMode();
void drawChooseStage();

// ポーズ処理　一時的にここに記述
void updatePause();
void drawPause();



// ここまで
#endif