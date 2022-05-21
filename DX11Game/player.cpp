//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Takeo
//
//=============================================================================
#include "player.h"
#include "bullet.h"
#include "flare.h"
#include "enemy.h"
#include "effect.h"
#include "collision.h"


//システム
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "input.h"
#include "scene.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************




//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static Player cPlayer;


//*****************************************************************************
// コンストラクタでヘッダー中身を通るようにする?
//*****************************************************************************
Player::Player() {}


//*****************************************************************************
// 初期化
//*****************************************************************************
void Player::Init()
{
	//PrintDebugProc("Player Init\n");

	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		PLAYER_TEXTURENAME, &g_pTexture);

	//変数初期化
	cPlayer.m_fPosition = PLAYER_DEFULT_POS;
	cPlayer.m_fSize = PLAYER_SIZE;
	cPlayer.m_fMaxPos = PLAYER_LIMITPOS;
	cPlayer.m_nLife = PLAYER_LIFE;
	
}


//*****************************************************************************
// 終了
//*****************************************************************************
void Player::Uninit()
{
	//PrintDebugProc("Player Uninit\n");
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}


//*****************************************************************************
// 更新
//*****************************************************************************
void Player::Update()
{
	//PrintDebugProc("Player Update\n");

	//-- キー入力による操作 --
	Player::Move();

	//死亡判定
	if (cPlayer.m_nLife <= 0)
	{
		SetScene(SCENE_GAMEOVER);
	}
}


//*****************************************************************************
// 描画
//*****************************************************************************
void Player::Draw()
{
	//PrintDebugProc("Player Draw\n");

	// プレイヤー描画
	SetPolygonPos(cPlayer.m_fPosition.x, cPlayer.m_fPosition.y);
	SetPolygonSize(cPlayer.m_fSize.x, cPlayer.m_fSize.y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}


//*****************************************************************************
// 操作
//*****************************************************************************
void Player::Move()
{

	if (GetKeyPress(VK_A))
	{
		if (cPlayer.m_fPosition.x >= -cPlayer.m_fMaxPos)
		{
			// 左移動
			PrintDebugProc("Left ON\n");
			cPlayer.m_fPosition.x -= PLAYER_MOVE_SPEED;
		}

	}
	else if (GetKeyPress(VK_D))
	{
		if (cPlayer.m_fPosition.x <= cPlayer.m_fMaxPos)
		{
			// 右移動
			PrintDebugProc("Right ON\n");
			cPlayer.m_fPosition.x += PLAYER_MOVE_SPEED;
		}
	}

	Bullet cBullet;
	if (GetKeyPress(VK_SPACE))
	{
		// 弾発射
		PrintDebugProc("Fire \n");
		cBullet.FireBullet(cPlayer.m_fPosition , 1);
		if (!m_bInterbal)
		{
			m_bInterbal = true;
		}
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Player::~Player() {}


//*****************************************************************************
// あたり判定
//*****************************************************************************
int Player::CollisionPlayer(float fX, float fY, float fR,
	float fDamage, float* pfX, float* pfY)
{
	Player p_cPlayer = cPlayer;
	

		// 衝突判定
		if (CollisionCircle(p_cPlayer.m_fPosition.x, p_cPlayer.m_fPosition.y, PLAYER_RADIUS, fX, fY, fR))
		{
			// 座標を返す
			if (pfX) *pfX = p_cPlayer.m_fPosition.x;

			if (pfY) *pfY = p_cPlayer.m_fPosition.y;

			StartEffect(&p_cPlayer.m_fPosition, EEFECT_DEAD000);
			cPlayer.m_nLife--;

			return 1;	// 0以上なら当たり
		}
	
	return -1;			// はずれ
}
