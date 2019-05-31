
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

Image terrene;//地上絵
Image selectBackGround;
Image constellation[12];//星座

Image rightCursor;
Image leftCursor;
Image decisionCursor;


VECTOR2 relativeVector(0, -800);//相対位置
VECTOR2 absoluteVector(600, 1200);//絶対位置

VECTOR2 rotationVector(VECTOR2 vector2, float angle);

float constellationPositionAngle[12];
void initializeSelect()
{
	InitImage(&terrene, getTexture(textureLoaderNS::STAGE_SELECT_IMAGE), 0, 0, 1200, 900);
	InitImage(&selectBackGround,  getTexture(textureLoaderNS::BACK_GROUND), -1200, -450, 3600, 2700);
	InitImage(&constellation[0],  getTexture(textureLoaderNS::CONSTELLATION01), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[1],  getTexture(textureLoaderNS::CONSTELLATION02), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[2],  getTexture(textureLoaderNS::CONSTELLATION03), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[3],  getTexture(textureLoaderNS::CONSTELLATION04), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[4],  getTexture(textureLoaderNS::CONSTELLATION05), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[5],  getTexture(textureLoaderNS::CONSTELLATION06), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[6],  getTexture(textureLoaderNS::CONSTELLATION07), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[7],  getTexture(textureLoaderNS::CONSTELLATION08), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[8],  getTexture(textureLoaderNS::CONSTELLATION09), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[9],  getTexture(textureLoaderNS::CONSTELLATION10), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[10], getTexture(textureLoaderNS::CONSTELLATION11), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&constellation[11], getTexture(textureLoaderNS::CONSTELLATION12), absoluteVector.x, absoluteVector.y, 64, 64);
	InitImage(&rightCursor, getTexture(textureLoaderNS::RIGHT_CURSOR), WINDOW_CENTER_X+150, WINDOW_HEIGHT-150, 100, 100);
	InitImage(&leftCursor, getTexture(textureLoaderNS::LEFT_CURSOR), WINDOW_CENTER_X-250, WINDOW_HEIGHT - 150, 100, 100);
	InitImage(&decisionCursor, getTexture(textureLoaderNS::LEFT_CURSOR), WINDOW_CENTER_X-100, WINDOW_HEIGHT - 150, 200, 100);
	float angle = 0;
	for (int i = 0; i < 12; i++, angle += 30)
	{
		constellationPositionAngle[i] = angle;
	}

}

void updateSelect()
{
	VECTOR2 claculationVector;
	if (getMouseLButtonTrigger() || GetKeyboardDebugEnter())
	{
		VECTOR2 mouse(getMouseX(), getMouseY());
		//右側
		if (onImage(mouse, rightCursor) || getMouseX() > WINDOW_CENTER_X+300) {
			setAngle(&selectBackGround, selectBackGround.angle + 30);
			for (int i = 0; i < STAGE_NUM; i++) {
				constellationPositionAngle[i] += 30.0f;
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
		//左側
		if ( onImage(mouse,leftCursor) || getMouseX() < WINDOW_CENTER_X-300) {
			setAngle(&selectBackGround, selectBackGround.angle -30);
			for (int i = 0; i < STAGE_NUM; i++) {
				constellationPositionAngle[i] -= 30.0f;
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
		//決定
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
	//x = x * cosθ - y * sinθ
	//y = x * sinθ + y * cosθ
	result.x = vector2.x * cosf(radian) - vector2.y * sinf(radian);
	result.y = vector2.x * sinf(radian) + vector2.y * cosf(radian);
	return result;
}

