//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : Takeo
//
//=============================================================================
#include "enemy.h"
#include "collision.h"
#include "score.h"
#include "bullet.h"
#include "flare.h"
#include "effect.h"


//システム
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
// 構造体
//*****************************************************************************



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static Enemy cEnemy[ENEMY_SPOWN_MAX_ROWS * ENEMY_SPOWN_MAX_COLUMNS];

static float g_Timer;
static int g_RimitTimer;
static float g_nTopPos;



//*****************************************************************************
// コンストラクタでヘッダー中身を通るようにする?
//*****************************************************************************
Enemy::Enemy() {}



//*****************************************************************************
// 初期化
//*****************************************************************************
void Enemy::Init()
{
	//PrintDebugProc("Enemy Init\n");

	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMY_TEXTURENAME, &g_pTexture);

	//変数初期化
	cEnemy->Init_Enemy();

	g_Timer = 0.0f;
	g_RimitTimer = 60.0f;

	

	
	m_Down = false;
	
}



//*****************************************************************************
// 終了
//*****************************************************************************
void Enemy::Uninit()
{
	//PrintDebugProc("Enemy Uninit\n");
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);

	//変数初期化
	//Enemy* p_cEnemy = cEnemy;
}



//*****************************************************************************
// 更新
//*****************************************************************************
void Enemy::Update()
{
	//PrintDebugProc("Enemy Update\n");

	//変数初期化
	Enemy* p_cEnemy = cEnemy;
	Bullet* cBullet = new Bullet();

	//乱数保存用
	int randSave;

	//時間カウント
	g_Timer++;
	
	
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		//弾をランダムに発射
		if (p_cEnemy[randSave = rand() % m_MaxEnemy].m_Destroy == 0)
		{
			cBullet->FireBullet(p_cEnemy[randSave].m_fPosition, 2);
		}
		


		//消滅した数により行動スピードを上げる
		if (p_cEnemy->m_Destroy == 1 && p_cEnemy->m_CountCheck == false)
		{
			g_RimitTimer *= 0.98;
			p_cEnemy->m_CountCheck = true;
		}
		


		//g_nTimerが１以下の時のみ、下の行動を起こす
		if (g_Timer >= g_RimitTimer)
		{
			//下へ降りる
			if (p_cEnemy->m_Destroy == 1)continue;
			if (p_cEnemy->m_fPosition.x >= ENEMY_LIMITPOS)
			{
				PosDownR();
				p_cEnemy->m_Turn = true;
			}
			else if (p_cEnemy->m_fPosition.x <= -ENEMY_LIMITPOS)
			{
				PosDownL();
				p_cEnemy->m_Turn = false;
			}

			//移動の折り返し
			if (m_Down)
			{
				MoveR();
			}
			else if (!m_Down)
			{
				MoveL();
			}

			g_Timer = 0;

		}
	}
}



//*****************************************************************************
// 描画
//*****************************************************************************
void Enemy::Draw()
{
	//PrintDebugProc("Enemy Draw\n");

	SetPolygonTexture(g_pTexture);

	//変数初期化
	Enemy* p_cEnemy = cEnemy;
	
	// 敵描画
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		if (p_cEnemy->m_Destroy == 1) continue;

		SetPolygonPos(p_cEnemy->m_fPosition.x, p_cEnemy->m_fPosition.y);
		SetPolygonSize(p_cEnemy->m_fSize.x, p_cEnemy->m_fSize.y);
		
		DrawPolygon(GetDeviceContext());

		//PrintDebugProc("Init Enemy NO_%f\n", i);
	}
	
}



//*****************************************************************************
// 群体の下降処理
//*****************************************************************************
void Enemy::PosDownR()
{
	//変数初期化
	Enemy* p_cEnemy = cEnemy;

	
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		
		if (m_Down) continue;
		p_cEnemy->m_fPosition.y -= ENEMY_DISTANCE;	
	}
	
	m_Down = true;
}

void Enemy::PosDownL()
{
	//変数初期化
	Enemy* p_cEnemy = cEnemy;


	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		
		if (!m_Down) continue;
		p_cEnemy->m_fPosition.y -= ENEMY_DISTANCE;
	}

	m_Down = false;
}



//*****************************************************************************
// 群体の移動処理
//*****************************************************************************
void Enemy::MoveR()
{
	//変数初期化
	Enemy* p_cEnemy = cEnemy;


	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		if (p_cEnemy->m_Destroy == 0) 
		p_cEnemy->m_fPosition.x -= ENEMY_MOVE_SPEED;
	}
}

void Enemy::MoveL()
{
	//変数初期化
	Enemy* p_cEnemy = cEnemy;


	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		if (p_cEnemy->m_Destroy == 0)
		p_cEnemy->m_fPosition.x += ENEMY_MOVE_SPEED;
	}
}




//*****************************************************************************
// 敵初期化
//*****************************************************************************
void Enemy::Init_Enemy()
{
	int i = 0;

	for (int y = 0; y < ENEMY_SPOWN_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < ENEMY_SPOWN_MAX_ROWS; ++x, i++)
		{
			//変数初期化
			cEnemy[i].m_fPosition = ENEMY_DEFULT_POS;
			cEnemy[i].m_fPosition.x += ENEMY_DISTANCE * x;
			cEnemy[i].m_fPosition.y += ENEMY_DISTANCE * -y;
			cEnemy[i].m_fSize = ENEMY_SIZE;
			cEnemy[i].m_fMaxPos = ENEMY_LIMITPOS;
			cEnemy[i].m_Destroy = 0;
			cEnemy[i].m_CountCheck = false;
			cEnemy[i].m_Shot = false;
			cEnemy[i].m_Turn = false;
		}
	}
}


//*****************************************************************************
// デストラクタ
//*****************************************************************************
Enemy::~Enemy() {}



//*****************************************************************************
// あたり判定
//*****************************************************************************
int Enemy::CollisionEnemy(float fX, float fY, float fR,
	float fDamage, float* pfX, float* pfY)
{
	Enemy* p_cEnemy = cEnemy;
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++) 
	{

		// 無効ならスキップ
		if (p_cEnemy->m_Destroy == 1) continue;

		// 衝突判定
		if (CollisionCircle(p_cEnemy->m_fPosition.x,p_cEnemy->m_fPosition.y, ENEMY_RADIUS, fX, fY, fR)) 
		{
			// 座標を返す
			if (pfX) *pfX = p_cEnemy->m_fPosition.x;
			
			if (pfY) *pfY = p_cEnemy->m_fPosition.y;
			

			
				p_cEnemy->m_Destroy = 1;
				StartEffect(&p_cEnemy->m_fPosition, EEFECT_DEAD000);
				AddScore(100);
			
			return i;	// 0以上なら当たり
		}
	}
	return -1;			// はずれ
}




