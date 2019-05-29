#pragma once

#include "main.h"

namespace textureLoaderNS
{
	enum TEXTURE_NUMBER {
		SMALL_STAR,//êºêÏ0525
		BIG_STAR,//êºêÏ0525
		STAR3,//êºêÏ0525
		BLACK_HOLE,
		WHITE_HOLE,
		COMET01,
		COMET02,
		PLANET,
		WALL,
		WITCH,//êºêÏ0525
		MAGIC_CIRCLE,//êºêÏ0525
		FIRE,//êºêÏ0528
		TEXT_WINDOW,//êºêÏ0528
		TITLE_LOGO,
		TITLE_PRESS_ENTER,
		TITLE_NEW_GAME,
		TITLE_SELECT_STAGE,
		TITLE_CURSOR,
		THUM_STAGE01,
		THUM_STAGE02,
		THUM_STAGE03,
		THUM_STAGE04,
		THUM_STAGE05,
		THUM_STAGE06,
		THUM_STAGE07,
		THUM_STAGE08,
		THUM_STAGE09,
		PAUSE,
		PAUSE_BLACK,
		PAUSE_RETURN_TITLE,
		BACK_GROUND,
		MAX_TEXTURE,
	};
}

class TextureLoader
{
private:
	const char* textureName[textureLoaderNS::MAX_TEXTURE];
	LPDIRECT3DTEXTURE9 g_pD3DTexture[textureLoaderNS::MAX_TEXTURE];

public:
	TextureLoader();
	~TextureLoader();

	void load(LPDIRECT3DDEVICE9 pDevice);
	void release();

	LPDIRECT3DTEXTURE9* getTexture(int i) { return &g_pD3DTexture[i]; }
};

TextureLoader* getTextureLoader();
LPDIRECT3DTEXTURE9* getTexture(int i);
