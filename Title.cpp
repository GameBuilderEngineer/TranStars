#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include"textureLoader.h"

// 樋沼追加
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;
#include "read_text.h"
#include "Select_Game.h"
// ここまで

Image back;

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);

	// 樋沼追加
	//string info_file = "information.txt"; // 読み込みファイル名＝ステージ番号
	//read_Status_File(info_file);
	initSelectTitle();
	// ここまで

};
void updateTitle() {
	updateSelectTitle();	// 樋沼追加
};
void drawTitle() {
	DrawImage(&back);
	drawSelectTitle();	// 樋沼追加
};
void printTitle() {
	printSelectTitle();	// 樋沼追加
};
void unInitializeTitle() {};