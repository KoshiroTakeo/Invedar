//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Takeo
//
//=============================================================================
#include "tohchica.h"
#include "bullet.h"
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
static Tohchica cTohchica[(TOHCHICA_MAX_ROWS * TOHCHICA_MAX_COLUMNS) * 3];


//*****************************************************************************
// コンストラクタでヘッダー中身を通るようにする?
//*****************************************************************************
Tohchica::Tohchica() {}


//*****************************************************************************
// 初期化
//*****************************************************************************
void Tohchica::Init()
{
	//PrintDebugProc("Player Init\n");

	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		PLAYER_TEXTURENAME, &g_pTexture);

	//変数初期化
	cTohchica->Init_Tohchica();

}


//*****************************************************************************
// 終了
//*****************************************************************************
void Tohchica::Uninit()
{
	//PrintDebugProc("Player Uninit\n");
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}


//*****************************************************************************
// 更新
//*****************************************************************************
void Tohchica::Update()
{
	//PrintDebugProc("Player Update\n");

	
}


//*****************************************************************************
// 描画
//*****************************************************************************
void Tohchica::Draw()
{
	//PrintDebugProc("Player Draw\n");
	Tohchica* pTohchica = cTohchica;

	// プレイヤー描画
	SetPolygonPos(pTohchica->m_fPosition.x, pTohchica->m_fPosition.y);
	SetPolygonSize(pTohchica->m_fSize.x, pTohchica->m_fSize.y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());

	// 敵描画
	for (int i = 0; i < m_MaxTohchica; i++, pTohchica++)
	{
		if (pTohchica->m_nDestroy == 1) continue;

		SetPolygonPos(pTohchica->m_fPosition.x, pTohchica->m_fPosition.y);
		SetPolygonSize(pTohchica->m_fSize.x, pTohchica->m_fSize.y);

		DrawPolygon(GetDeviceContext());

	}
}

// トーチカ初期化
void Tohchica::Init_Tohchica()
{

	int i = 0;
	int n = 0;
	int t = 0;

	for (int y = 0; y < TOHCHICA_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < TOHCHICA_MAX_ROWS; ++x, i++)
		{
			cTohchica[i].m_fPosition = TOHCHICA_DEFULT_POS_LEFT;
			cTohchica[i].m_fPosition.x += TOHCHICA_DISTANCE * x;
			cTohchica[i].m_fPosition.y += TOHCHICA_DISTANCE * y;
			cTohchica[i].m_fSize = TOHCHICA_SIZE;
			cTohchica[i].m_nDestroy = 0;
		}
	}


	for (int y = 0; y < TOHCHICA_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < TOHCHICA_MAX_ROWS; ++x, i++)
		{
			cTohchica[i].m_fPosition = TOHCHICA_DEFULT_POS_CENTER;
			cTohchica[i].m_fPosition.x += TOHCHICA_DISTANCE * x;
			cTohchica[i].m_fPosition.y += TOHCHICA_DISTANCE * y;
			cTohchica[i].m_fSize = TOHCHICA_SIZE;
			cTohchica[i].m_nDestroy = 0;
		}
	}

	for (int y = 0; y < TOHCHICA_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < TOHCHICA_MAX_ROWS; ++x, i++)
		{
			cTohchica[i].m_fPosition = TOHCHICA_DEFULT_POS_RIGHT;
			cTohchica[i].m_fPosition.x += TOHCHICA_DISTANCE * x;
			cTohchica[i].m_fPosition.y += TOHCHICA_DISTANCE * y;
			cTohchica[i].m_fSize = TOHCHICA_SIZE;
			cTohchica[i].m_nDestroy = 0;
		}
	}

	PrintDebugProc("PlayerBullet Init\n");
}



//*****************************************************************************
// デストラクタ
//*****************************************************************************
Tohchica::~Tohchica() {}


//*****************************************************************************
// あたり判定
//*****************************************************************************
int Tohchica::CollisionTohchica(float fX, float fY, float fR,
	float fDamage, float* pfX, float* pfY)
{
	Tohchica* p_cTohchica = cTohchica;

	for (int i = 0; i < m_MaxTohchica; i++, p_cTohchica++)
	{
		// 衝突判定
		if (CollisionCircle(p_cTohchica->m_fPosition.x, p_cTohchica->m_fPosition.y, TOHCHICA_RADIUS, fX, fY, fR))
		{
			// 座標を返す
			if (pfX) *pfX = p_cTohchica->m_fPosition.x;

			if (pfY) *pfY = p_cTohchica->m_fPosition.y;

			StartEffect(&p_cTohchica->m_fPosition, EEFECT_DEAD000);
			p_cTohchica->m_nDestroy = 1;

			return 1;	// 0以上なら当たり
		}
	}

	return -1;			// はずれ
}
