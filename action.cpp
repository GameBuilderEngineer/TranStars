#include "action.h"
#include "SmallStarFrame.h"
#include "BigStarFrame.h"
#include "Stage.h"
#include "game.h"

void actFitStar(ObjStr* star, ObjStr* frame, EffList* eff) {
	star->m_use = false;//星を消滅

	if (getStageClass()->starNumPluss()) changeScene(RESULT);//星の数が規定値に達していたらシーン変更

	makeEffect(eff, ePARTICLE, star);//エフェクト発生
}

void actFitSmallStar(ObjStr* star, ObjStr* frame, EffList* eff) {
	if (frame->m_mode >= 0) return;
	fixSmallStar(star, frame);
	actFitStar(star, frame, eff);
}
void actFitBigStar(ObjStr* star, ObjStr* frame, EffList* eff) {
	if (frame->m_mode >= 0) return;
	fixBigStar(star, frame);
	actFitStar(star, frame, eff);
}

void actSplit(ObjStr* collisionObject, ObjStr* sweeper, EffList* eff) {
	collisionObject->m_use = false;//当たった側を壊す処理
	makeEffect(eff, eSPLIT, collisionObject);
}

void actReflect(ObjStr* collisionObject, ObjStr* reflection) {
	float rCol, rRef;
	if (reflection->m_rect.x > reflection->m_rect.y) rRef = reflection->m_rot + D3DX_PI / 2.0f;
	else rRef = reflection->m_rot;

	rCol = atan2f(collisionObject->m_speed.y, collisionObject->m_speed.x);
	rCol = rRef - (rCol - rRef);

	float sCol = sqrtf(powf(collisionObject->m_speed.x, 2.0f) + powf(collisionObject->m_speed.y, 2.0f));

	collisionObject->m_speed = { cosf(rCol) * sCol,sinf(rCol) * sCol };
	collisionObject->m_rot = rCol;
}
