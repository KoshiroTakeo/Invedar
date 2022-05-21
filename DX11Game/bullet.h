//=============================================================================
//
// 弾処理 [bullet.h]
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
#define  BULLET_MOVE_SPEED 8
#define  BULLET_SIZE	   (XMFLOAT2(5.0f,10.0f))
#define  ENEMY_BULLET_DEFULT_POS  (XMFLOAT2( 5000.0f, 5000.0f))
#define  PLAYER_BULLET_DEFULT_POS (XMFLOAT2(-10000.0f,-10000.0f))
#define  DESTROY_POS       400
#define  ENEMY_BULLET_MAX  100
#define  PLAYER_BULLET_MAX 10

#define BULLET_TEXTURENAME	L"data/texture/player000.png"	// テクスチャファイル名


//*****************************************************************************
// クラス定義
//*****************************************************************************
class Bullet :public Object
{
public:
	Bullet(void);
	~Bullet(void);

	void Init();
	void Update();
	void Draw();
	void Uninit();

    int FireBullet(XMFLOAT2, int);

private:
	int  m_bFireSwitch;
	int  m_nStat;
	
	int m_nMaxBullet = ENEMY_BULLET_MAX;

	//bool m_bPlayerFire;
	//bool m_bEnemyFire;
	bool m_bFire;

	void Init_PlayerBullet();
	void Init_EnemyBullet();

};