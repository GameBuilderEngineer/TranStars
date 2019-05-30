#include "textWindow.h"
#include "image.h"
#include "textureLoader.h"
#include <string.h>

void updateIcon(TextW* textW);
void setIcon();

TextDX font;//フォント
Image imageW;//ウィンドウ画像

struct {
	Image m_img;//アイコン画像
	D3DXVECTOR3 m_pos;//座標
	float m_c1, m_c2;
}Icon;

void initializeTextW(TextW* textW) {
	float sizeY = float(WINDOW_WIDTH) / 771.0f * 112.0f;

	textW->m_mode = 0;
	textW->m_text = NULL;
	textW->m_NUM = 0;
	textW->m_written = 0;
	textW->m_INTERVAL_FRAME = 0;
	textW->m_frame = 0;
	textW->m_x = 0;textW->m_y = 0;

	createTextDX(&font, TEXT_FONT_SIZE, true, false, "メイリオ");//西川0530
	InitImage(&imageW, getTexture(textureLoaderNS::TEXT_WINDOW), float(textW->m_x), float(textW->m_y), float(WINDOW_WIDTH), sizeY);

	Icon.m_pos = { 0.0f,0.0f,0.0f };
	Icon.m_c1 = Icon.m_c2 = 0.0f;
	InitImage(&Icon.m_img, getTexture(textureLoaderNS::WITCH), Icon.m_pos.x, Icon.m_pos.y, ICON_SIZE_MIN, ICON_SIZE_MAX);
}
void uninitializeTextW(TextW* textW){
	releaseTextW(textW);
}

void updateTextW(TextW* textW,bool key){
	if (textW->m_mode == 0) return;
	if (textW->m_mode != 2) {
		if (textW->m_written >= textW->m_NUM)
			textW->m_mode = 2;
		else {
			textW->m_frame++;
			if (textW->m_frame > textW->m_INTERVAL_FRAME) {
				textW->m_frame = 0;
				textW->m_written++;
			}
			if (key)
				textW->m_written = textW->m_NUM;
		}
	}
	else
		if (key)
			releaseTextW(textW);

	updateIcon(textW);
}

void updateIcon(TextW* textW) {
	float size = (ICON_SIZE_MIN + ICON_SIZE_MAX) /2.0f + (ICON_SIZE_MAX - ICON_SIZE_MIN) * sinf(Icon.m_c1);
	Icon.m_c1 += 0.010f; Icon.m_c2 += 0.006f;
	Icon.m_pos = { float(textW->m_x) + float(imageW.width) - 200.0f + cosf(Icon.m_c2) * imageW.height /2.0f,
		float(textW->m_y) + float(imageW.height) / 2.0f + cosf(Icon.m_c1) * (imageW.height / 2.0f + size / 3.0f),
		sinf(Icon.m_c1) };

	float l= cosf(Icon.m_c2),r;
	if (l < -0.6f) r = -1.0f;
	else if (l > -0.4f) r = 1.0f;
	else r = (l + 0.5f) * 10.0f;
	setSize(&Icon.m_img, size * r, size);
	setPosition(&Icon.m_img, Icon.m_pos.x - size * r / 2.0f , Icon.m_pos.y - size / 2.0f);
}

void drawTextW(TextW* textW) {
	if (textW->m_mode == 0) return;

	if (Icon.m_pos.z < 0.0f) DrawImage(&Icon.m_img);//ウィンドウの裏側
	DrawImage(&imageW);
	if (Icon.m_pos.z >= 0.0f) DrawImage(&Icon.m_img);//ウィンドウの表側
}

void printTextW(TextW* textW) {
	if (textW->m_mode == 0) return;
	char* txt = new char[textW->m_written * 2 + 1];//テキストの内容

	strncpy_s(txt, textW->m_written * 2 + 1, textW->m_text, textW->m_written * 2);
	printTextDX(&font, txt, textW->m_x + TEXT_FONT_SIZE, textW->m_y + TEXT_FONT_SIZE);
	if (txt != NULL)
 		free(txt);
}

void setTextW(TextW* textW,const char* txt,int interval,int x,int y) {
	textW->m_mode = 1;//書き中

	int n = strlen(txt) / 2;//もらった全角文字列の文字数
	textW->m_text = (char*)malloc(sizeof(char) * ((n + 2) * 2 + 1));
	strncpy_s(&textW->m_text[0], n * 2 + 1, txt, n * 2);
	strncpy_s(&textW->m_text[n * 2], (2) * 2 + 1, "　▼", (2) * 2);
	textW->m_NUM = n + 2;//全角文字数
	textW->m_written = 0;

	textW->m_INTERVAL_FRAME = interval;
	textW->m_frame = 0;
	textW->m_x = x; textW->m_y = y;

	setPosition(&imageW, float(x), float(y));
}

void setIcon(){
	Icon.m_pos = { 0.0f,0.0f,0.0f };
	Icon.m_c1 = Icon.m_c2 = 0.0f;
}

void releaseTextW(TextW* textW) {
	textW->m_mode = 0;//off
	if (textW->m_text != NULL) {
		delete(textW->m_text);
		textW->m_text = NULL;
	}
}