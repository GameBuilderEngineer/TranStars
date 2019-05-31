#pragma once
#include "image.h"
#include "textDX.h"

#define TEXT_FONT_SIZE (30)
#define ICON_SIZE_MIN (160.0f)
#define ICON_SIZE_MAX (192.0f)

typedef struct{
	short m_mode;//���[�h 0:�����O 1�F�����r�� 2:�����I�����(�����҂�)
	char* m_text;//�e�L�X�g�̓��e
	int m_NUM;//�I�[���������̑S�p������
	int m_written;//m_num�̂������ɏ�������
	int m_INTERVAL_FRAME;//���̕����������t���[����
	int m_frame;//���̕����������t���[����
	int m_x, m_y;//�����o���ʒu
}TextW;

void initializeTextW(TextW* textW);
void uninitializeTextW(TextW* textW);
void updateTextW(TextW* textW, bool key);
void drawTextW(TextW* textW);
void printTextW(TextW* textW);

void setTextW(TextW* textW, const char* txt, int interval, int x, int y);
void releaseTextW(TextW* textW);
