#include "action.h"
#include "effect.h"
#include "stage.h"

float resetRot(float r);

bool actFitStar(ObjStr* star, ObjStr* frame) {
//	¯‚ðŒÅ’è‚·‚éˆ—
//	˜g‚ðˆê”t‚É‚·‚éˆ—
	makeEffect(getEffect(), ePARTICLE, star);
}

bool actSplit(ObjStr* collisionObject, ObjStr* stardust) {
//	collisionObject->m_use = false;//“–‚½‚Á‚½‘¤‚ð‰ó‚·ˆ—
	makeEffect(getEffect(), eSPLIT, collisionObject);
}

bool actReflect(ObjStr* collisionObject, ObjStr* reflection) {
	float rCol, rRef;
	if (reflection->m_rect.x > reflection->m_rect.y) rRef = reflection->m_rot + D3DX_PI / 2.0f;
	else rRef = reflection->m_rot;

	rCol = atan2f(collisionObject->m_speed.y, collisionObject->m_speed.x);
	rCol = rRef - (rCol - rRef);

	float sCol = sqrtf(powf(collisionObject->m_speed.x, 2.0f) + powf(collisionObject->m_speed.y, 2.0f));

	collisionObject->m_speed = { cosf(rCol) * sCol,sinf(rCol) * sCol };
	collisionObject->m_rot = rCol;
	return true;
}

float resetRot(float r) {
	for (;;) {
		if (r < 0.0f) r += D3DX_PI * 2.0f;
		if (r > D3DX_PI * 2.0f) r -= D3DX_PI * 2.0f;
		break;
	}
	return r;
}