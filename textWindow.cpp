#include "textWindow.h"
#include "textDX.h"
#include "image.h"
#include "textureLoader.h"
#include <string.h>
#include "input.h"
#define _CRT_SECURE_NO_WARNINGS

struct TextW{
	bool m_use;//use�t���O
	char* m_text;//�e�L�X�g�̓��e
	short m_mode;//���[�h 0:�����O 1�F�����r�� 2:�����I�����(�����҂�)
	int m_num;//�e�L�X�g��
	int m_written;//���ɏ������e�L�X�g��
	int m_x,m_y;//�����o���ʒu
	TextDX m_font;//�t�H���g
	Image m_image;//�g
}textW;

void initializeTextW() {
	float sizeY = float(WINDOW_WIDTH) / 771.0f * 112.0f; float height = 0.0f;

	textW.m_use = false;
	textW.m_mode = 0;
	textW.m_num = 0;
	textW.m_written = 0;
	textW.m_x = 30;
	textW.m_y = int(height) + 30;

	createTextDX(&textW.m_font, 30, true, false, "���C���I");
	InitImage(&textW.m_image, getTexture(textureLoaderNS::TEXT_WINDOW), 0.0f, height, float(WINDOW_WIDTH), sizeY);


	setTextW("��������");
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
	char* txt = (char*)malloc(sizeof(char) * (textW.m_written * 2 + 1));//�e�L�X�g�̓��e
	strncpy_s(txt, textW.m_written * 2 + 1, textW.m_text, textW.m_written * 2);
	printTextDX(&textW.m_font, txt, textW.m_x, textW.m_y);
	if (sizeof(txt) != 0)
		free(txt);
}

void setTextW(const std::string &text) {
	textW.m_use = true;
	textW.m_text = (char*)malloc(sizeof((char*)text.c_str()));
	textW.m_text = (char*)text.c_str();
	textW.m_mode = 1;//������
	textW.m_num = (sizeof((char*)text.c_str()) / sizeof(char) - 1) / 2;//�e�L�X�g��
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