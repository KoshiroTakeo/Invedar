//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : Takeo
//
//=============================================================================
#include "bullet.h"
#include "polygon.h"
#include "Texture.h"
#include "enemy.h"
#include "player.h"
#include "tohchica.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static Bullet cEnemyBullet[ENEMY_BULLET_MAX];
static Bullet cPlayerBullet[PLAYER_BULLET_MAX];
static bool g_bPlayer_InterbalFire; //Player用発射フラグ



//*****************************************************************************
// コンストラクタでヘッダー中身を通るようにする?
//*****************************************************************************
Bullet::Bullet() {}


//=============================================================================
// 弾の初期化処理
//=============================================================================
void Bullet::Init()
{
	//PrintDebugProc("Bullet Init\n");

	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		BULLET_TEXTURENAME, &g_pTexture);

	cEnemyBullet->Init_EnemyBullet();
	cPlayerBullet->Init_PlayerBullet();

}


//=============================================================================
// 弾の終了処理
//=============================================================================
void Bullet::Uninit()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}


//=============================================================================
// 弾の更新処理
//=============================================================================
void Bullet::Update()
{
	//PrintDebugProc("Bullet Update\n");


	Enemy cEnemy;
	Player cPlayer;
	Tohchica cTohchica;

	Bullet* pEnemyBullet  = cEnemyBullet;
	Bullet* pPlayerBullet = cPlayerBullet;



	//プレイヤーの弾 
	for (int i = 0; i < PLAYER_BULLET_MAX; ++i, ++pPlayerBullet)
	{
		if (pPlayerBullet->m_bFire == true)
		{
			//PrintDebugProc("%d\n" , pPlayerBullet->m_fPosition.y);
			pPlayerBullet->m_fPosition.y += BULLET_MOVE_SPEED;

			// 弾と敵の接触判定
			if (pPlayerBullet->m_fPosition.y >= pPlayerBullet->m_fMaxPos || cEnemy.CollisionEnemy(pPlayerBullet->m_fPosition.x, 
				pPlayerBullet->m_fPosition.y, pPlayerBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pPlayerBullet->m_bFire = false;
				cPlayerBullet->m_fPosition = PLAYER_BULLET_DEFULT_POS;
			}

			// 弾とトーチカの接触判定
			if (pPlayerBullet->m_fPosition.y >= pPlayerBullet->m_fMaxPos || cTohchica.CollisionTohchica(pPlayerBullet->m_fPosition.x,
				pPlayerBullet->m_fPosition.y, pPlayerBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pPlayerBullet->m_bFire = false;
				cPlayerBullet->m_fPosition = PLAYER_BULLET_DEFULT_POS;
			}
		}
	}



	//敵の弾
	for (int i = 0; i < ENEMY_BULLET_MAX; ++i, ++pEnemyBullet)
	{
		if (pEnemyBullet->m_bFire == true)
		{
			//PrintDebugProc("%d\n" , pEnemyBullet->m_fPosition.y);
			pEnemyBullet->m_fPosition.y -= BULLET_MOVE_SPEED;

			// 弾とプレイヤーの接触判定
			if (pEnemyBullet->m_fPosition.y <= -pEnemyBullet->m_fMaxPos || 
				cPlayer.CollisionPlayer(pEnemyBullet->m_fPosition.x, pEnemyBullet->m_fPosition.y, pEnemyBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pEnemyBullet->m_bFire = false;
				pEnemyBullet->m_fPosition = ENEMY_BULLET_DEFULT_POS;
				//PrintDebugProc("EnemyBullet Start\n");
			}

			//弾とトーチカの接触判定
			if (pEnemyBullet->m_fPosition.y <= -pEnemyBullet->m_fMaxPos ||
				cTohchica.CollisionTohchica(pEnemyBullet->m_fPosition.x, pEnemyBullet->m_fPosition.y, pEnemyBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pEnemyBullet->m_bFire = false;
				pEnemyBullet->m_fPosition = ENEMY_BULLET_DEFULT_POS;
				//PrintDebugProc("EnemyBullet Start\n");
			}

		}

	}

}


//=============================================================================
// 弾の描画処理
//=============================================================================
void Bullet::Draw()
{
	//PrintDebugProc("Bullet Draw\n");

	Bullet* pEnemyBullet = cEnemyBullet;
	Bullet* pPlayerBullet = cPlayerBullet;

	SetPolygonSize(BULLET_SIZE.x, BULLET_SIZE.y);
	SetPolygonTexture(g_pTexture);

	
	// プレイヤー弾描画
	for (int i = 0; i < PLAYER_BULLET_MAX; ++i, ++pPlayerBullet)
	{
		SetPolygonPos(pPlayerBullet->m_fPosition.x, pPlayerBullet->m_fPosition.y);
		DrawPolygon(GetDeviceContext());
	}


	// 敵弾描画
	for (int i = 0; i < ENEMY_BULLET_MAX; ++i, ++pEnemyBullet)
	{
		SetPolygonPos(pEnemyBullet->m_fPosition.x, pEnemyBullet->m_fPosition.y);
		DrawPolygon(GetDeviceContext());
	}
}


//=============================================================================
// 弾の発射処理
//=============================================================================
int Bullet::FireBullet(XMFLOAT2 pos, int nWho)
{
	Bullet* pPlayerBullet = cPlayerBullet;
	Bullet* pEnemyBullet  = cEnemyBullet;
	
	
	switch (nWho)
	{
		case 1://プレイヤーの弾
			for (int i = 0; i < PLAYER_BULLET_MAX; ++i, ++pPlayerBullet)
			{
				if (pPlayerBullet->m_bFire == false)
				{
					//PrintDebugProc("PlayerFire \n");
					pPlayerBullet->m_fPosition = pos;
					pPlayerBullet->m_bFire = true;
				}
				return i;
			}
			break;

		case 2://敵の弾
			for (int i = 0; i < ENEMY_BULLET_MAX; ++i, ++pEnemyBullet)
			{
				if (pEnemyBullet->m_bFire == false)
				{
					//PrintDebugProc("EnemyFire \n");
					pEnemyBullet->m_fPosition = pos;
					pEnemyBullet->m_bFire = true;
				}
				return i;
			}
			break;
	}

	return -1;
}



//*****************************************************************************
// 初期化
//*****************************************************************************

// 敵
void Bullet::Init_EnemyBullet()
{
	//変数初期化
	for (int i = 0; i < ENEMY_BULLET_MAX; ++i)
	{
		cEnemyBullet[i].m_fPosition = ENEMY_BULLET_DEFULT_POS;
		cEnemyBullet[i].m_fSize = BULLET_SIZE;
		cEnemyBullet[i].m_fMaxPos = DESTROY_POS;
		cEnemyBullet[i].m_bFireSwitch = 0;
		cEnemyBullet[i].m_bFire = false;
	}
	PrintDebugProc("EnemyBullet Init\n");
}

// 味方
void Bullet::Init_PlayerBullet()
{
	//変数初期化
	for (int i = 0; i < PLAYER_BULLET_MAX; ++i)
	{
		cPlayerBullet[i].m_fPosition = PLAYER_BULLET_DEFULT_POS;
		cPlayerBullet[i].m_fSize = BULLET_SIZE;
		cPlayerBullet[i].m_fMaxPos = DESTROY_POS;
		cPlayerBullet[i].m_bFireSwitch = 0;
		cPlayerBullet[i].m_bFire = false;
	}

	PrintDebugProc("PlayerBullet Init\n");
}




//*****************************************************************************
// デストラクタ
//*****************************************************************************
Bullet::~Bullet() {}