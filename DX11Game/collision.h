//=============================================================================
//
// 衝突判定処理 [collision.h]
// Author : Takeo
//
//=============================================================================
#pragma once

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int CollisionCircle(float fAx, float fAy, float fAr,
	float fBx, float fBy, float fBr);
int CollisionRect(float fAx, float fAy,
	float fAw, float fAh, float fBx, float fBy,
	float fBw, float fBh);
