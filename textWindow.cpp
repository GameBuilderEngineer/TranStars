#include "textWindow.h"
#include "textDX.h"
#include "image.h"
#include "textureLoader.h"
#include <string.h>
#include "input.h"
#define _CRT_SECURE_NO_WARNINGS

struct TextW{
	bool m_use;//useフラグ
	char* m_text;//テキストの内容
	short m_mode;//モード 0:書く前 1：書き途中 2:書き終わった(反応待ち)
	int m_num;//テキスト量
	int m_written;//既に書いたテキスト量
	int m_x,m_y;//書き出し位置
	TextDX m_font;//フォント
	Image m_image;//枠
}textW;

void initializeTextW() {
	float sizeY = float(WINDOW_WIDTH) / 771.0f * 112.0f; float height = 0.0f;

	textW.m_use = false;
	textW.m_mode = 0;
	textW.m_num = 0;
	textW.m_written = 0;
	textW.m_x = 30;
	textW.m_y = int(height) + 30;

	createTextDX(&textW.m_font, 30, true, false, "メイリオ");
	InitImage(&textW.m_image, getTexture(textureLoaderNS::TEXT_WINDOW), 0.0f, height, float(WINDOW_WIDTH), sizeY);


	setTextW("ああああ");
}
void uninitializeTextW(){}

void updateTextW(){
	if (!textW.m_use) return;
	if (textW.m_written > textW.m_num)
		releaseTextW();
	else
		textW.m_written++;
}
void drawTextW() {
	if (!textW.m_use) return;
//	setPosition(&textW.m_image, textW.m_image.position.x, textW.m_image.position.y);
	DrawImage(&textW.m_image);
}
void printTextW() {
	if (!textW.m_use) return;
	char* txt = (char*)malloc(sizeof(char) * (textW.m_written * 2 + 1));//テキストの内容
	strncpy_s(txt, textW.m_written * 2 + 1, textW.m_text, textW.m_written * 2);
	printTextDX(&textW.m_font, txt, textW.m_x, textW.m_y);
	if (sizeof(txt) != 0)
		free(txt);
}

void setTextW(const std::string &text) {
	textW.m_use = true;
	textW.m_text = (char*)malloc(sizeof((char*)text.c_str()));
	textW.m_text = (char*)text.c_str();
	textW.m_mode = 1;//書き中
	textW.m_num = (sizeof((char*)text.c_str()) / sizeof(char) - 1) / 2;//テキスト量
	textW.m_written = 0;
}

void releaseTextW() {
	textW.m_use = false;
	if (textW.m_text != NULL) {
		free(textW.m_text);
		textW.m_text = NULL;
	}
	textW.m_mode = 0;//off
}