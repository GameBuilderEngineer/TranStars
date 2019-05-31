#include "Title.h"
#include "textDX.h"
#include "Image.h"
#include"textureLoader.h"
#include "input.h"

// 樋沼追加
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;
#include "read_text.h"
#include "Select.h"
#include "game.h"
// ここまで

enum TITLE_ITEM
{
	BACK,
	TITLE_LOGO,
	START_LOGO,
	TITLE_ITEM_NUM,
};

struct Item{
	Image image;
	LPDIRECT3DTEXTURE9* texture;
	float x;
	float y;
	float width;
	float height;
};

Item titleItem[TITLE_ITEM_NUM] =
{
	{Image(),getTexture(textureLoaderNS::BACK_GROUND),0,0,1200,900},//背景
	{Image(),getTexture(textureLoaderNS::TITLE_LOGO),0,-100,1200,900},//タイトルロゴ
	{Image(),getTexture(textureLoaderNS::TITLE_START),(float)(WINDOW_CENTER_X-130), 700, 260, 40},//ゲームスタート
};

const int BACK_STAR_NUM = 100;
Image backStars[BACK_STAR_NUM];
VECTOR2 moveDirectionStar(-5, 3);

void drawStars();

void initializeTitle() {
	for (int i = 0; i < TITLE_ITEM_NUM; i++)
	{
		InitImage(&titleItem[i].image, titleItem[i].texture, titleItem[i].x, titleItem[i].y, titleItem[i].width, titleItem[i].height);
	}
	for (int i = 0; i < BACK_STAR_NUM; i++)
	{
		InitImage(&backStars[i], getTexture(textureLoaderNS::SMALL_STAR), (float)(rand() % WINDOW_WIDTH), (float)(rand() % WINDOW_HEIGHT), 32, 32);
	}
};

void updateTitle() {
	for (int i = 0; i < BACK_STAR_NUM; i++)
	{
		VECTOR2 v = moveDirectionStar + (VECTOR2)backStars[i].position;
		if (v.x > WINDOW_WIDTH)v.x = 0;
		if (v.x < 0)v.x = WINDOW_WIDTH;
		if (v.y > WINDOW_HEIGHT)v.y = 0;
		if (v.y < 0)v.y = WINDOW_HEIGHT;
		setPosition(&backStars[i], v.x, v.y);
		setAngle(&backStars[i], backStars[i].angle + 1);
	}
	if (getMouseLButtonTrigger() || GetKeyboardDebugEnter()) {
		if (onImage(D3DXVECTOR2((float)getMouseX(), (float)getMouseY()), titleItem[START_LOGO].image) || GetKeyboardDebugEnter())
		{
			changeScene(SELECT);//ステージ選択画面へ遷移
		}
	}
};

void drawTitle() {
	for (int i = 0; i < TITLE_ITEM_NUM; i++)
	{
		DrawImage(&titleItem[i].image);
		if (i == BACK)drawStars();
	}
};

void drawStars()
{
	for (int i = 0; i < BACK_STAR_NUM; i++)
	{
		DrawImage(&backStars[i]);
	}
}

void printTitle() {

};

void unInitializeTitle() {
	for (int i = 0; i < TITLE_ITEM_NUM; i++)
	{
		UninitImage(&titleItem[i].image);
	}
	for (int i = 0; i < BACK_STAR_NUM; i++)
	{
		UninitImage(&backStars[i]);
	}
};