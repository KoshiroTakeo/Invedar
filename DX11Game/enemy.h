//=============================================================================
//
// プレイヤー処理 [Enemy.h]
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
#define  ENEMY_SIZE	(XMFLOAT2(20.0f,20.0f))
#define  ENEMY_DEFULT_POS (XMFLOAT2(0.0f,100.0f))
#define  ENEMY_LIMITPOS   300
#define  ENEMY_MOVE_SPEED 5.0
#define  ENEMY_SPOWN_MAX_ROWS    10 //横の行数
#define  ENEMY_SPOWN_MAX_COLUMNS 6  //縦の列数
#define  ENEMY_COLLISION_RADIUS 24
#define  ENEMY_DISTANCE 20
#define  ENEMY_RADIUS 10.0

#define ENEMY_TEXTURENAME	L"data/texture/inverder_Player.png"	// テクスチャファイル名

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Enemy : public Object
{
public:
	Enemy(void);
	~Enemy(void);

	void Init();
	void Update();
	void Draw();
	void Uninit();

	int CollisionEnemy(float fX, float fY, float fR, float fDamage, float* pfX, float* pfY);


private:
	//-- メンバ変数 --
	int m_MaxEnemy = ENEMY_SPOWN_MAX_ROWS * ENEMY_SPOWN_MAX_COLUMNS;
	bool m_Down;
	bool m_Turn;
	bool m_CountCheck;
	bool m_Shot;
	int m_Destroy;
	float AddSpeed;

	void Init_Enemy();
	void PosDownR();
	void PosDownL();
	void MoveR();
	void MoveL();
	

	
};
