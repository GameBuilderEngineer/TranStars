
#include "textureLoader.h"
#include "Image.h"
#include "textDX.h"
#include "Select.h"
#include "game.h"
#include "input.h"
#include "game.h"
#include "object.h"

int cursor = STAGE02;
int getSelectStage() { return cursor; }

Image terrene;//�n��G
Image selectBackGround;
Image constellation[12];//����

Image rightCursor;
Image leftCursor;
Image decisionCursor;


VECTOR2 relativeVector(0, -1000);//���Έʒu
VECTOR2 absoluteVector(600 - 160, 1200);//��Έʒu

VECTOR2 rotationVector(VECTOR2 vector2, float angle);

float constellationPositionAngle[12];
void initializeSelect()
{
	InitImage(&terrene, getTexture(textureLoaderNS::STAGE_SELECT_IMAGE), 0, 0, 1200, 900);
	InitImage(&selectBackGround,  getTexture(textureLoaderNS::TITLE_BACK_GROUND), -1200, -450, 3600, 2700);
	InitImage(&constellation[0],  getTexture(textureLoaderNS::THUM_STAGE01), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[1],  getTexture(textureLoaderNS::THUM_STAGE02), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[2],  getTexture(textureLoaderNS::THUM_STAGE03), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[3],  getTexture(textureLoaderNS::THUM_STAGE04), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[4],  getTexture(textureLoaderNS::THUM_STAGE05), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[5],  getTexture(textureLoaderNS::THUM_STAGE06), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[6],  getTexture(textureLoaderNS::THUM_STAGE07), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[7],  getTexture(textureLoaderNS::THUM_STAGE08), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[8],  getTexture(textureLoaderNS::THUM_STAGE09), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[9],  getTexture(textureLoaderNS::THUM_STAGE10), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[10], getTexture(textureLoaderNS::THUM_STAGE11), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&constellation[11], getTexture(textureLoaderNS::THUM_STAGE12), absoluteVector.x, absoluteVector.y, 320, 320);
	InitImage(&rightCursor, getTexture(textureLoaderNS::RIGHT_CURSOR), WINDOW_CENTER_X+150, WINDOW_HEIGHT-150, 100, 100);
	InitImage(&leftCursor, getTexture(textureLoaderNS::LEFT_CURSOR), WINDOW_CENTER_X-250, WINDOW_HEIGHT - 150, 100, 100);
	InitImage(&decisionCursor, getTexture(textureLoaderNS::DECISION_CURSOR), WINDOW_CENTER_X-100, WINDOW_HEIGHT - 150, 200, 100);
	float angle = 0;
	VECTOR2 claculationVector;
	for (int i = 0; i < 12; i++, angle += 30)
	{
		constellationPositionAngle[i] = angle;
		claculationVector = rotationVector(relativeVector, constellationPositionAngle[i]);
		VECTOR2 newPosition = absoluteVector + claculationVector;
		setPosition(&constellation[i], newPosition.x, newPosition.y);
	}

}

void updateSelect()
{
	VECTOR2 claculationVector;
	if (getMouseLButtonTrigger() || GetKeyboardDebugEnter())
	{
		VECTOR2 mouse(getMouseX(), getMouseY());
		//�E��
		if (onImage(mouse, rightCursor) || getMouseX() > WINDOW_CENTER_X+300) {
			setAngle(&selectBackGround, selectBackGround.angle + 30);
			for (int i = 0; i < STAGE_NUM; i++) {
				constellationPositionAngle[i] -= 30.0f;
				claculationVector = rotationVector(relativeVector, constellationPositionAngle[i]);
				VECTOR2 newPosition = absoluteVector + claculationVector;
				setPosition(&constellation[i], newPosition.x, newPosition.y);
			}
			cursor++;
			if (cursor >= STAGE_NUM)
			{
				cursor = 0;
			}
		}
		//����
		if ( onImage(mouse,leftCursor) || getMouseX() < WINDOW_CENTER_X-300) {
			setAngle(&selectBackGround, selectBackGround.angle -30);
			for (int i = 0; i < STAGE_NUM; i++) {
				constellationPositionAngle[i] += 30.0f;
				claculationVector = rotationVector(relativeVector, constellationPositionAngle[i]);
				VECTOR2 newPosition = absoluteVector + claculationVector;
				setPosition(&constellation[i], newPosition.x, newPosition.y);
			}
			cursor--;
			if (cursor < 0)
			{
				cursor = STAGE_NUM-1;
			}
		}
		//����
		if (onImage(mouse, decisionCursor) || GetKeyboardDebugEnter())
		{
			changeScene(STAGE);
		}
	}
}

void drawSelect()
{
	DrawImage(&selectBackGround);
	for (int i = 0; i < 12; i++) {
		DrawImage(&constellation[i]);
	}
	DrawImage(&terrene);
	DrawImage(&rightCursor);
	DrawImage(&leftCursor);
	DrawImage(&decisionCursor);

}

void printSelect()
{
	printTextDX(getDebugFont(), "selectStage:", 800, 30, cursor + 1);
}

void unInitializeSelect()
{

}


VECTOR2 rotationVector(VECTOR2 vector2,float angle)
{
	VECTOR2 result;
	float radian = D3DXToRadian(angle);
	//x = x * cos�� - y * sin��
	//y = x * sin�� + y * cos��
	result.x = vector2.x * cosf(radian) - vector2.y * sinf(radian);
	result.y = vector2.x * sinf(radian) + vector2.y * cosf(radian);
	return result;
}

