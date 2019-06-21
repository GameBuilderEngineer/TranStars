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
	textureName[textureLoaderNS::SMALL_STAR] = { "TEXTURE/star_yellow.png" };//西川0525
	textureName[textureLoaderNS::BIG_STAR] = { "TEXTURE/star_orange.png" };//西川0525
	textureName[textureLoaderNS::SMALL_STAR_FRAME] = { "TEXTURE/star_black.png" };//西川0525
	textureName[textureLoaderNS::BIG_STAR_FRAME] = { "TEXTURE/star_black.png" };//西川0525
	textureName[textureLoaderNS::REFLECTION ] = { "TEXTURE/wall01.PNG" };//西川0525
	textureName[textureLoaderNS::BLACK_HOLE] = { "TEXTURE/BH.png" };//西川0530
	textureName[textureLoaderNS::WHITE_HOLE] = { "TEXTURE/WH.PNG" };//西川0530
	textureName[textureLoaderNS::COMET01] = { "TEXTURE/comet001_.png" };
	textureName[textureLoaderNS::COMET02] = { "TEXTURE/comet002_.PNG" };
	textureName[textureLoaderNS::PLANET] = { "TEXTURE/planet.jpg" };
	textureName[textureLoaderNS::WALL] = { "TEXTURE/block.png" };
	textureName[textureLoaderNS::WITCH] = { "TEXTURE/witch.png" };//西川0525
	textureName[textureLoaderNS::MAGIC_CIRCLE] = { "TEXTURE/magic_circle.PNG" };//西川0525
	textureName[textureLoaderNS::FIRE] = { "TEXTURE/fire.png" };//西川0528
	textureName[textureLoaderNS::TEXT_WINDOW] = { "TEXTURE/text_window_.png" };//西川0528
	textureName[textureLoaderNS::PARTICLE_STAR] = { "TEXTURE/star3.PNG" };//西川0528

	textureName[textureLoaderNS::CONSTELLATION01] = { "TEXTURE/ohitsuji.png" };
	textureName[textureLoaderNS::CONSTELLATION02] = { "TEXTURE/oushi.png" };
	textureName[textureLoaderNS::CONSTELLATION03] = { "TEXTURE/hutago.png" };
	textureName[textureLoaderNS::CONSTELLATION04] = { "TEXTURE/tenbin.png" };
	textureName[textureLoaderNS::CONSTELLATION05] = { "TEXTURE/kani.png" };
	textureName[textureLoaderNS::CONSTELLATION06] = { "TEXTURE/shishi.png" };
	textureName[textureLoaderNS::CONSTELLATION07] = { "TEXTURE/otome.png" };
	textureName[textureLoaderNS::CONSTELLATION08] = { "TEXTURE/sasori.png" };
	textureName[textureLoaderNS::CONSTELLATION09] = { "TEXTURE/ite.png" };
	textureName[textureLoaderNS::CONSTELLATION10] = { "TEXTURE/yagi.png" };
	textureName[textureLoaderNS::CONSTELLATION11] = { "TEXTURE/mizugame.png" };
	textureName[textureLoaderNS::CONSTELLATION12] = { "TEXTURE/uo.png" };
	
	// 樋沼追加
	textureName[textureLoaderNS::BACK_GROUND] = { "TEXTURE/gameBG.png" };
	textureName[textureLoaderNS::TITLE_BACK_GROUND] = { "TEXTURE/selectBackGround.png" };
	textureName[textureLoaderNS::TITLE_LOGO] = { "TEXTURE/titleLogo.png" };
	textureName[textureLoaderNS::TITLE_START] = { "TEXTURE/press_start.png" };
	textureName[textureLoaderNS::TITLE_NEW_GAME] = { "TEXTURE/new_game.png" };
	textureName[textureLoaderNS::TITLE_SELECT_STAGE] = { "TEXTURE/stage_select.png" };
	textureName[textureLoaderNS::STAGE_SELECT_IMAGE] = { "TEXTURE/stageSelectImage.png" };
	textureName[textureLoaderNS::LEFT_CURSOR] = { "TEXTURE/left_button.png" };
	textureName[textureLoaderNS::RIGHT_CURSOR] = { "TEXTURE/right_button.png" };
	textureName[textureLoaderNS::DECISION_CURSOR] = { "TEXTURE/dicision.png" };
	textureName[textureLoaderNS::PAUSE] = { "TEXTURE/pause.png" };
	textureName[textureLoaderNS::PAUSE_BLACK] = { "TEXTURE/black.png" };
	textureName[textureLoaderNS::PAUSE_RETURN_TITLE] = { "TEXTURE/return_title.png" };
	textureName[textureLoaderNS::THUM_STAGE01] = { "TEXTURE/stage1.png" };
	textureName[textureLoaderNS::THUM_STAGE02] = { "TEXTURE/stage2.png" };
	textureName[textureLoaderNS::THUM_STAGE03] = { "TEXTURE/stage3.png" };
	textureName[textureLoaderNS::THUM_STAGE04] = { "TEXTURE/stage4.png" };
	textureName[textureLoaderNS::THUM_STAGE05] = { "TEXTURE/stage5.png" };
	textureName[textureLoaderNS::THUM_STAGE06] = { "TEXTURE/stage6.png" };
	textureName[textureLoaderNS::THUM_STAGE07] = { "TEXTURE/stage7.png" };
	textureName[textureLoaderNS::THUM_STAGE08] = { "TEXTURE/stage8.png" };
	textureName[textureLoaderNS::THUM_STAGE09] = { "TEXTURE/stage9.png" };
	textureName[textureLoaderNS::THUM_STAGE10] = { "TEXTURE/stage10.png" };
	textureName[textureLoaderNS::THUM_STAGE11] = { "TEXTURE/stage11.png" };
	textureName[textureLoaderNS::THUM_STAGE12] = { "TEXTURE/stage12.png" };

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
