//=============================================================================
//
// Õ“Ë”»’èˆ— [collision.cpp]
// Author : Takeo
//
//=============================================================================
#include "collision.h"

//=============================================================================
// ‰~“¯m‚ÌÕ“Ë”»’è
//=============================================================================
int CollisionCircle(float fAx, float fAy, float fAr,
	float fBx, float fBy, float fBr)
{
	float fDx = fAx - fBx;
	float fDy = fAy - fBy;
	float fSr = fAr + fBr;
	return fDx * fDx + fDy * fDy <= fSr * fSr;
}

//=============================================================================
// ‹éŒ`“¯m‚ÌÕ“Ë”»’è
//=============================================================================
int CollisionRect(float fAx, float fAy,
	float fAw, float fAh, float fBx, float fBy,
	float fBw, float fBh)
{
	return fAx - fAw <= fBx + fBw &&
		fBx - fBw <= fAx + fAw &&
		fAy - fAh <= fBy + fBh &&
		fBy - fBh <= fAy + fAh;
}
