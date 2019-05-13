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
	textureName[textureLoaderNS::BACK_GROUND] = { "TEXTURE/gameBG.png" };
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
