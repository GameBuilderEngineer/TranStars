#pragma once
#include "image.h"
#include "textDX.h"

#define TEXT_FONT_SIZE (30)
#define ICON_SIZE_MIN (160.0f)
#define ICON_SIZE_MAX (192.0f)

typedef struct{
	short m_mode;//モード 0:書く前 1：書き途中 2:書き終わった(反応待ち)
	char* m_text;//テキストの内容
	int m_NUM;//終端文字抜きの全角文字数
	int m_written;//m_numのうち既に書いた量
	int m_INTERVAL_FRAME;//次の文字を書くフレーム数
	int m_frame;//次の文字を書くフレーム数
	int m_x, m_y;//書き出し位置
}TextW;

void initializeTextW(TextW* textW);
void uninitializeTextW(TextW* textW);
void updateTextW(TextW* textW, bool key);
void drawTextW(TextW* textW);
void printTextW(TextW* textW);

void setTextW(TextW* textW, const char* txt, int interval, int x, int y);
void releaseTextW(TextW* textW);
