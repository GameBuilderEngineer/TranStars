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
	textureName[textureLoaderNS::SMALL_STAR] = { "TEXTURE/star1.PNG" };	//����0525
	textureName[textureLoaderNS::BIG_STAR] = { "TEXTURE/star2.PNG" };	//����0525
	textureName[textureLoaderNS::STAR3] = { "TEXTURE/star3.PNG" };		//����0525
	textureName[textureLoaderNS::BLACK_HOLE] = { "TEXTURE/BH_kari.png" };
	textureName[textureLoaderNS::WHITE_HOLE] = { "TEXTURE/WH_kari.png" };
	textureName[textureLoaderNS::COMET01] = { "TEXTURE/comet001.jpg" };
	textureName[textureLoaderNS::COMET02] = { "TEXTURE/comet002.jpg" };
	textureName[textureLoaderNS::PLANET] = { "TEXTURE/planet.jpg" };
	textureName[textureLoaderNS::WALL] = { "TEXTURE/WALL_kari.png" };
	textureName[textureLoaderNS::WITCH] = { "TEXTURE/witch.png" };		//����0525
	textureName[textureLoaderNS::MAGIC_CIRCLE] = { "TEXTURE/magic_circle.PNG" };//����0525
	textureName[textureLoaderNS::FIRE] = { "TEXTURE/fire.png" };//����0528
	textureName[textureLoaderNS::TEXT_WINDOW] = { "TEXTURE/text_window_.png" };//����0528

	textureName[textureLoaderNS::CONSTELLATION01] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION02] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION03] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION04] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION05] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION06] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION07] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION08] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION09] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION10] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION11] = { "TEXTURE/star_.jpg" };
	textureName[textureLoaderNS::CONSTELLATION12] = { "TEXTURE/star_.jpg" };
	
	// ����ǉ�
	textureName[textureLoaderNS::BACK_GROUND] = { "TEXTURE/gameBG.png" };
	textureName[textureLoaderNS::TITLE_LOGO] = { "TEXTURE/titleLogo.png" };
	textureName[textureLoaderNS::TITLE_START] = { "TEXTURE/pressEnter.png" };
	textureName[textureLoaderNS::TITLE_NEW_GAME] = { "TEXTURE/new_game.png" };
	textureName[textureLoaderNS::TITLE_SELECT_STAGE] = { "TEXTURE/stage_select.png" };
	textureName[textureLoaderNS::STAGE_SELECT_IMAGE] = { "TEXTURE/stageSelectImage.png" };
	textureName[textureLoaderNS::LEFT_CURSOR] = { "TEXTURE/left_button.png" };
	textureName[textureLoaderNS::RIGHT_CURSOR] = { "TEXTURE/right_button.png" };
	textureName[textureLoaderNS::DECISION_CURSOR] = { "TEXTURE/pressEnter.png" };
	textureName[textureLoaderNS::PAUSE] = { "TEXTURE/pause.png" };
	textureName[textureLoaderNS::PAUSE_BLACK] = { "TEXTURE/black.png" };
	textureName[textureLoaderNS::PAUSE_RETURN_TITLE] = { "TEXTURE/return_title.png" };
	textureName[textureLoaderNS::THUM_STAGE01] = { "TEXTURE/stage01.png" };

	// �ꎞ�I�ɃX�e�[�W2�ȍ~�����摜�z�u
	textureName[textureLoaderNS::THUM_STAGE02] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE03] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE04] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE05] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE06] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE07] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE08] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE09] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE10] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE11] = { "TEXTURE/stage01.png" };
	textureName[textureLoaderNS::THUM_STAGE12] = { "TEXTURE/stage01.png" };

}


TextureLoader::~TextureLoader()
{
	release();
}


void TextureLoader::load(LPDIRECT3DDEVICE9 pDevice)
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�ւ̃|�C���^
			textureName[i],		// �t�@�C���̖��O
			&g_pD3DTexture[i]);	// �ǂݍ��ރ������[
	}
}

void TextureLoader::release()
{
	for (int i = 0; i < textureLoaderNS::MAX_TEXTURE; i++) {
		if (g_pD3DTexture[i] != NULL)
		{// �e�N�X�`���̊J��
			g_pD3DTexture[i]->Release();
			g_pD3DTexture[i] = NULL;
		}
	}
}
