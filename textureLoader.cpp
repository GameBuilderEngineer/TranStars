#include "TextureLoader.h"

TextureLoader textureLoader;
TextureLoader* getTextureLoader()
{
	return &textureLoader;
}
LPDIRECT3DTEXTURE9* getTexture(int i)
{
	return textureLoader.getTexture(i);
}

TextureLoader::TextureLoader()
{
//西川 0.22
	textureName[textureLoaderNS::STAR] = { "TEXTURE/Star_kari.png" };
	textureName[textureLoaderNS::BLACK_HOLE] = { "TEXTURE/BH_kari.png" };
	textureName[textureLoaderNS::WHITE_HOLE] = { "TEXTURE/WH_kari.png" };
	textureName[textureLoaderNS::COMET] = { "TEXTURE/comet.jpg" };
	textureName[textureLoaderNS::PLANET] = { "TEXTURE/planet.jpg" };
	textureName[textureLoaderNS::WALL] = { "TEXTURE/WALL_kari.h" };

	// 樋沼追加
	textureName[textureLoaderNS::BACK_GROUND] = { "TEXTURE/gameBG.png" };
	textureName[textureLoaderNS::TITLE_LOGO] = { "TEXTURE/title_logo.png" };
	textureName[textureLoaderNS::TITLE_PRESS_ENTER] = { "TEXTURE/press_enter.png" };
	textureName[textureLoaderNS::TITLE_NEW_GAME] = { "TEXTURE/new_game.png" };
	textureName[textureLoaderNS::TITLE_SELECT_STAGE] = { "TEXTURE/stage_select.png" };
	textureName[textureLoaderNS::TITLE_CURSOR] = { "TEXTURE/cursor.png" };
	textureName[textureLoaderNS::PAUSE] = { "TEXTURE/pause.png" };
	textureName[textureLoaderNS::PAUSE_BLACK] = { "TEXTURE/black.png" };
	textureName[textureLoaderNS::PAUSE_RETURN_TITLE] = { "TEXTURE/return_title.png" };
	textureName[textureLoaderNS::THUM_STAGE01] = { "TEXTURE/stage01.png" };

	// 一時的にステージ2以降も白画像配置
	textureName[textureLoaderNS::THUM_STAGE02] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE03] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE04] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE05] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE06] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE07] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE08] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE09] = { "TEXTURE/stage01.png" };

	//textureName[textureLoaderNS::THUM_STAGE02] = { "TEXTURE/stage02.png" };
	//textureName[textureLoaderNS::THUM_STAGE03] = { "TEXTURE/stage03.png" };
	//textureName[textureLoaderNS::THUM_STAGE04] = { "TEXTURE/stage04.png" };
	//textureName[textureLoaderNS::THUM_STAGE05] = { "TEXTURE/stage05.png" };
	//textureName[textureLoaderNS::THUM_STAGE06] = { "TEXTURE/stage06.png" };
	//textureName[textureLoaderNS::THUM_STAGE07] = { "TEXTURE/stage07.png" };
	//textureName[textureLoaderNS::THUM_STAGE08] = { "TEXTURE/stage08.png" };
	// ここまで

}


TextureLoader::~TextureLoader()
{
	release();
}


void TextureLoader::load(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,	// デバイスへのポインタ
			textureName[i],		// ファイルの名前
			&g_pD3DTexture[i]);	// 読み込むメモリー
	}
}

void TextureLoader::release()
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++) {
		if (g_pD3DTexture[i] != NULL)
		{// テクスチャの開放
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}
