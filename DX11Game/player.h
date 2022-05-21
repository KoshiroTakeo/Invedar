//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Takeo
//
//=============================================================================
#pragma once


//*****************************************************************************
// include
//*****************************************************************************
#include "main.h"
#include "Object.h"


//*****************************************************************************
// define
//*****************************************************************************
#define  PLAYER_SIZE	(XMFLOAT2(20.0f,20.0f))
#define  PLAYER_DEFULT_POS (XMFLOAT2(0.0f,-200.0f))
#define  PLAYER_LIMITPOS   300
#define  PLAYER_MOVE_SPEED 4
#define  PLAYER_RADIUS 20
#define  PLAYER_LIFE   5

#define PLAYER_TEXTURENAME	L"data/texture/inverder_Player.png"	// テクスチャファイル名

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Player : public Object
{
public:
	Player(void);
	~Player(void);

	void Init() ;
	void Update() ;
	void Draw();
	void Uninit();

	int CollisionPlayer(float fX, float fY, float fR, float fDamage, float* pfX, float* pfY);

	

private:
	//-- メンバ変数 --
	bool  m_bInterbal;

	void Move();

};
