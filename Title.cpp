#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include"textureLoader.h"

// ����ǉ�
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;
#include "read_text.h"
#include "Select_Game.h"
// �����܂�

Image back;

void initializeTitle() {
	InitImage(&back, getTexture(textureLoaderNS::BACK_GROUND), 0, 0, 1200, 900);

	// ����ǉ�
	//string info_file = "information.txt"; // �ǂݍ��݃t�@�C�������X�e�[�W�ԍ�
	//read_Status_File(info_file);
	initSelectTitle();
	// �����܂�

};
void updateTitle() {
	updateSelectTitle();	// ����ǉ�
};
void drawTitle() {
	DrawImage(&back);
	drawSelectTitle();	// ����ǉ�
};
void printTitle() {
	printSelectTitle();	// ����ǉ�
};
void unInitializeTitle() {};