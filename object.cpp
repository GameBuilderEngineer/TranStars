//����
#include "object.h"
#include "collision.h"
//#include "stdlib.h"//malloc�p
#include"textureLoader.h"
#include "read_text.h"
#include "textDX.h"
#include "input.h"
#include "fileLoader.h"
#include "SmallStar.h"
#include "BlackHole.h"
#include "WhiteHole.h"
#include "SmallStar.h"
#include "BigStar.h"
#include "comet.h"
#include "PopStar.h"
#include "Cursor.h"
#include "PopComet.h"
#include "BigStarFrame.h"
#include "SmallStarFrame.h"
#include "StarDust.h"
#include "StarLine.h"
#include "Reflection.h"

//����
//�������܂����B
//�X�e�[�W�\���̂ƃI�u�W�F�N�g�\���̖̂������A���ꂼ�ꍬ�݂��Ă���Ɣ��f�����̂ŁA
//�t�@�C�����������܂����B
//���̃I�u�W�F�N�gcpp�́A��{�I�ɂ́A��̃I�u�W�F�N�g�ɍ�p����֐��A�f�[�^�ō\�����܂����B


//�I�u�W�F�N�g���Z�b�g����n���[�J���֐�
//ObjStr cleanObj(int i);
Image cleanTex(void);

//�I�u�W�F�N�g���ʏ�������֐�
//�@�\���ƂɃt�@�C�����������������ǂ��Ǝv���܂��B�ikanno�j
void updatePlayer(ObjStr* p_obj);



void resetStar(ObjStr* p_obj);
//���낢�뉞�p�ł������Ȍv�Z�����I�֐�

/*�R���W�������X�g�ɕK�v�����Ȃ���
obID/obType/pos/rot/scl/coltype

�A�N�V�������X�g

�G�t�F�N�g���X�g
*/


void initializeObject(ObjStr *obj,int id, int objType,VECTOR2 position,float angle,ObjStr* others,int otherNum){
	//����F2019/5/26���C

	//���I�u�W�F�N�g�̏����l
	obj->m_type = (objTypes)objType;
	obj->m_id = id;
	obj->m_pos = position;
	obj->m_rot = angle;

	switch (obj->m_type) {
	case CHARA_BLACKHOLE://�u���b�N�z�[��
		initializeBlackHole(obj, others,otherNum);
		break;
	case CHARA_WHITEHOLE://�z���C�g�z�[��
		initializeWhiteHole(obj);
		break;
	case UI_CURSOR://����0525
		//�J�[�\��
		initializeCursor(obj);
		break;
	case CHARA_SMALL_STAR://��
		initializeSmallStar(obj);
		break;
	case CHARA_BIG_STAR://��
		initializeBigStar(obj);
		break;
	case CHARA_COMET://覐�
		initializeComet(obj);
		break;
	case POP_STAR://�����|�b�v����ꏊ
		initializePopStar(obj);
		break;
	case POP_COMET://覐Δ����ꏊ
		initializePopComet(obj);
		break;
	case CHARA_SMALL_STARFRAME://���i���j��Ƃ߂�^
		initializeSmallStarFrame(obj);
		break;
	case CHARA_BIG_STARFRAME://���i��j��Ƃ߂�^
		initializeBigStarFrame(obj);
		break;
	case CHARA_STARDUST://�ǁE���̂����̏�Q��
		initializeStarDust(obj);
		break;
	case STAGE_STARLINE://���Ɛ������Ԑ�
		initializeStarLine(obj);
		break;
	case STAGE_REFLECTION://���̂𔽎˂����
		initializeReflection(obj);
		break;
	default:
		obj->m_scl = { 1.0f,1.0f };
		obj->m_speed = { 0.0f,0.0f };
		obj->m_accel = { 0.0f,0.0f };
		obj->m_attract = { 0.0f,0.0f };
		obj->m_time = -1;
		obj->m_mode = -1;
		obj->m_rad = 50.0f;
		obj->m_rect = { 100.0f,100.0f };
		obj->m_image.g_pD3DTexture = *getTexture(textureLoaderNS::BACK_GROUND);
		obj->m_image.width = 100.0f;
		obj->m_image.height = 100.0f;
		obj->m_image.playAnime = false;
		obj->m_image.ANIME_TIME = 1;
		obj->m_image.ANIME_PATTERN = 1;
		obj->m_image.DIVIDE_U = 1;
		obj->m_image.DIVIDE_V = 1;
		InitImage(&obj->m_image, getTexture(textureLoaderNS::MAGIC_CIRCLE), obj->m_pos.x, obj->m_pos.y, 160.0f, 160.0f);
		break;
	}
}

void uninitializeObject(ObjStr* obj) {
	if (obj != NULL) {
//		free(Obj);
		//delete[]obj;
		//obj = NULL;
		//�����free/delete���Q�A���ł��ƃ��o�� ���� NULL�ۂ�free/delete����镪�ɂ͕��C �炵���̂ł�������
	}
	//while (ShowCursor(TRUE) != 0);//�}�E�X��\��
}

void updateObject(ObjStr* obj) {
	switch (obj->m_type) {//�^�C�v���Ƃɏ�������
	case CHARA_BLACKHOLE:
		//�u���b�N�z�[��
		updateBlackHole(obj);
		break;
	case CHARA_WHITEHOLE:
		//�z���C�g�z�[��
		updateWhiteHole(obj);
		break;
	case UI_CURSOR://���� 0525
		//�u���b�N�z�[���u���J�[�\��
		updateCursor(obj);
		break;
	case CHARA_SMALL_STAR:
		//���i���j
		updateSmallStar(obj);
		break;
	case CHARA_BIG_STAR:
		//���i��j
		break;
	case CHARA_COMET:
		//覐�
		break;
	case POP_STAR:
		//���i���j����������ꏊ
		break;
	case POP_COMET:
		//覐΂���������ꏊ
		break;
	case CHARA_SMALL_STARFRAME:
		//���i���j���͂܂�^
		break;
	case CHARA_BIG_STARFRAME:
		//���i��j���͂܂�^
		break;
	case CHARA_STARDUST:
		//���̕�
		break;
	case STAGE_STARLINE:
		//���Ɛ������Ԑ�
		break;
	case STAGE_REFLECTION:
		//���Ɛ������Ԑ�
		break;
	default:
		break;
	}
	//�I�u�W�F�N�g�̊�{����
	if (obj->m_use == false)return;
	obj->m_pos += obj->m_accel;
	setPosition(&(obj->m_image), obj->m_pos.x , obj->m_pos.y);
	setAngle(&(obj->m_image), obj->m_image.angle);
}

void drawObject(ObjStr* obj){
	//�S�ẴI�u�W�F�N�g��`��@�����ꂾ�ƕ`�揇���^�C�v���Ƃɑ�������ł��Ȃ��̂ŁA�`��p�̃��X�g����邱�ƂɂȂ�̂���
	if (obj->m_use == false) return;
	DrawImage(&(obj->m_image));
}

void printObject(ObjStr* obj) {
	txtLineReset(int(obj->m_pos.y + obj->m_image.height));//�������s�ʒu���Z�b�g
	printTextDX(getDebugFont(), "type", int(obj->m_pos.x), txtLineBreak(), int(obj->m_type));
	printTextDX(getDebugFont(), "id", int(obj->m_pos.x), txtLineBreak(), obj->m_id);
	printTextDX(getDebugFont(), "x", int(obj->m_pos.x), txtLineBreak(), obj->m_pos.x);
	printTextDX(getDebugFont(), "y", int(obj->m_pos.x), txtLineBreak(), obj->m_pos.y);

	/*************************************************
	printTextDX(getDebugFont(), "Length",0, 90, objectLength(&p_stgobj->m_Obj[plID],&p_stgobj->m_Obj[bhID]));
	printTextDX(getDebugFont(), "BH_att.x", 0, 120, p_stgobj->m_Obj[bhID].m_attract.x);
	printTextDX(getDebugFont(), "BH_att.y", 0, 150, p_stgobj->m_Obj[bhID].m_attract.y);
	printTextDX(getDebugFont(), "PL_speed.x", 0, 180, p_stgobj->m_Obj[plID].m_speed.x);
	printTextDX(getDebugFont(), "PL_speed.y", 0, 210, p_stgobj->m_Obj[plID].m_speed.y);
	printTextDX(getDebugFont(), "PL_accel.x", 0, 240, p_stgobj->m_Obj[plID].m_accel.x);
	printTextDX(getDebugFont(), "PL_accel.y", 0, 270, p_stgobj->m_Obj[plID].m_accel.y);
	****************************************************/

	//�v���C���[ID���������Ďg�p
	//D3DXVECTOR2 center = computeRotatedBox(&obj[plID]);
	//printTextDX(getDebugFont(), "PL_corner.����x", 0, 90,  obj[plID].m_corner[0].x);
	//printTextDX(getDebugFont(), "PL_corner.����y", 0, 120, obj[plID].m_corner[0].y);
	//printTextDX(getDebugFont(), "PL_corner.�E��x", 0, 150, obj[plID].m_corner[1].x);
	//printTextDX(getDebugFont(), "PL_corner.�E��y", 0, 180, obj[plID].m_corner[1].y);
	//printTextDX(getDebugFont(), "PL_corner.����x", 0, 210, obj[plID].m_corner[2].x);
	//printTextDX(getDebugFont(), "PL_corner.����y", 0, 240, obj[plID].m_corner[2].y);
	//printTextDX(getDebugFont(), "PL_corner.�E��x", 0, 270, obj[plID].m_corner[3].x);
	//printTextDX(getDebugFont(), "PL_corner.�E��y", 0, 300, obj[plID].m_corner[3].y);

	//printTextDX(getDebugFont(), "PL_center.x", 0, 330, center.x);
	//printTextDX(getDebugFont(), "PL_center.y", 0, 360, center.y);

}

float getObjectSizeLonger(ObjStr* obj) {
	float dgnl = sqrtf((obj->m_rect.x * obj->m_rect.x +
		obj->m_rect.y * obj->m_rect.y)) / 2.0f;
	if (dgnl >= obj->m_rad) return dgnl;
	else return obj->m_rad;
}//����0519  �I�u�W�F�N�g�̎������o�̂����A��`�̑Ίp���Ɣ��a�Œ�������Ԃ�


/////�ȉ��I�u�W�F�N�g�Z�b�g�n���[�J���֐�

//ObjStr cleanObj(int i) {//Obj�����Z�b�g
//	return {
//		NO_TYPE,
//		short(i),
//		false,
//		NULL,
//		NULL,
//		{0.0f,0.0f},
//		0.0f,
//		{0.0f,0.0f},
//		{0.0f,0.0f},
//		{0.0f,0.0f},
//		{0.0f,0.0f},
//		int(0),
//		short(0),
//		0.0f,
//		{0.0f,0.0f}
////		cleanTex()
//	};
//}

Image cleanTex(void) {//Tex�����Z�b�g
	Image nullTex;
	InitImage(&nullTex, getTexture(textureLoaderNS::TEXTURE_NUMBER(0)), 0, 0, 1, 1);
	return nullTex;
}

//void setObjFromFile(ObjStr *obj, int i, Stage* p_fromstage){
//	//��������X�e�[�W�f�[�^�̒�����I�u�W�F�N�g���Z�b�g
//
//	if (StubObj->m_type != NO_TYPE) {//�X�e�[�W�f�[�^���璆�g�𒼐ڂ��炦�΂�������
//		obj->m_type = StubObj->m_type;
//		obj->m_id = StubObj->m_id;
//		obj->m_use = false;
//		obj->m_ptr = obj;
//		obj->m_tar = NULL;
//
//		obj->m_pos = StubObj->m_pos;
//		obj->m_rot = StubObj->m_rot;
//		obj->m_scl = StubObj->m_scl;
//
//		obj->m_speed = D3DXVECTOR2{0.0f,0.0f};
//		obj->m_accel = StubObj->m_accel;
//		obj->m_attract = StubObj->m_attract;
//
//		obj->m_time = StubObj->m_time;
//		obj->m_mode = StubObj->m_mode;
//
//		obj->m_rad = StubObj->m_rad;
//		obj->m_rect = StubObj->m_rect;
//		obj->m_rect = { StubTex->width,StubTex->height };
//	}
//	else {//�X�e�[�W�f�[�^����̃^�C�v�ɂȂ��Ă�����
//		*obj = cleanObj(i);
//	}
//}

//void setObjNotFrom(ObjStr *obj, int i, int objnum) {
	//UI�ȂǁA�X�e�[�W���Ƃɕς��Ȃ��̂Ńt�@�C���ɕۑ�����K�v���Ȃ��A���񂱂���Őݒ肷��΂����I�u�W�F�N�g���Z�b�g
	//obj->m_id = i;
	//obj->m_use = true;
	//switch (i - objnum) {
	//case 0:
	//	obj->m_type = UI_CURSOR;
	//	//����0525
	//	obj->m_rect = { StubTex[int(UI_CURSOR)].width,StubTex[int(UI_CURSOR)].height };//����0525
	//	break;
	//case 1:
	//	obj->m_type = UI_EFFECT;
	//	obj->m_pos = { 720.0f,480.0f };
	//	break;
	//default:
	//	obj->m_type = UI_HP;
	//	obj->m_pos = { 0.0f,0.0f };
	//	break;
	//}
//}

//void setObjTex(ObjStr* obj, int i) {//Obj��StubTex�̒��g���Z�b�g
//	if (obj->m_type != NO_TYPE) {
//		//StubTexture *p_tex = &(StubTex[int(obj->m_type)]);
//		if (p_tex->m_type != NO_TYPE) {
//			if (obj->m_image.playAnime == false) {//�Î~�悾������
//				InitImage(&(obj->m_image), getTexture(StubTex[int(obj->m_type)].texture), obj->m_pos.x, obj->m_pos.y,
//					p_tex->width, p_tex->height);
//			}
//			else {//�A�j����������
//				InitAnimeImage(&(obj->m_image), getTexture(StubTex[int(obj->m_type)].texture), obj->m_pos.x, obj->m_pos.y,
//					p_tex->width, p_tex->height,
//					p_tex->ANIME_TIME, p_tex->ANIME_PATTERN, p_tex->DIVIDE_U, p_tex->DIVIDE_V);
//			}
//		}
//		else {//�e�N�X�`���f�[�^����̃^�C�v�ɂȂ��Ă�����
//			obj->m_image = cleanTex();
//		}
//	}
//	else {//�I�u�W�F�N�g�f�[�^����̃^�C�v�ɂȂ��Ă�����
//		obj->m_image = cleanTex();
//	}
//}

void updatePlayer(ObjStr* obj) {
	//p_obj->m_rot = D3DX_PI / 4;
	obj->m_speed.x += obj->m_accel.x;	// �����x�𑬓x�։��Z����
	obj->m_speed.y += obj->m_accel.y;	// �����x�𑬓x�։��Z����

	if (obj->m_speed.x > 2.0f)
	{
		obj->m_speed.x = 2.0f;
	}
	if (obj->m_speed.y > 2.0f)
	{
		obj->m_speed.y = 2.0f;
	}

	if (obj->m_speed.x < -2.0f)
	{
		obj->m_speed.x = -2.0f;
	}
	if (obj->m_speed.y < -2.0f)
	{
		obj->m_speed.y = -2.0f;
	}

	//p_obj->m_pos.x += p_obj->m_speed.x;			// �ʒu���𑬓x�ōX�V
	//p_obj->m_pos.y += p_obj->m_speed.y;			// �ʒu���𑬓x�ōX�V

};




// 2�̃I�u�W�F�N�g�Ԃ̋�����(�Z�o����/�߂�/�Ԃ�)
float objectLength(ObjStr* p_obj1, ObjStr* p_obj2)
{
	D3DXVECTOR2 toTarget;
	toTarget.x = p_obj1->m_pos.x - p_obj2->m_pos.x;
	toTarget.y = p_obj1->m_pos.y - p_obj2->m_pos.y;
	float length = D3DXVec2Length(&toTarget);
	return length;
};

// �I�u�W�F�N�g1�ɑ΂���I�u�W�F�N�g2�̕����x�N�g����߂�
D3DXVECTOR2 objectDirection(ObjStr* p_obj1, ObjStr* p_obj2)
{
	D3DXVECTOR2 dir;
	dir.x = p_obj1->m_pos.x - p_obj2->m_pos.x;
	dir.y = p_obj1->m_pos.y - p_obj2->m_pos.y;
	// ���K�����đ傫����1�ɂ���
	D3DXVec2Normalize(&dir, &dir);
	return dir;
}

void resetStar(ObjStr* p_obj)
{
	p_obj->m_pos = D3DXVECTOR2{ WINDOW_WIDTH , 450.0f };
	p_obj->m_speed = D3DXVECTOR2{ -1.0f,0.0f };
	p_obj->m_accel = D3DXVECTOR2{ 0.0f,0.0f };
}
void setWhiteHole(ObjStr* obj, ObjStr* whiteHole)
{ obj->whiteHole = whiteHole; }