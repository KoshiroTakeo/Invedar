//=============================================================================
//
// スコア表示処理 [score.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "score.h"
#include "polygon.h"
#include "Texture.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FRAME_TEXTURENAME	L"data/texture/frame_score.png"	// テクスチャファイル名

#define FRAME_SIZE_X		340								// ポリゴンのサイズ
#define FRAME_SIZE_Y		80								// ポリゴンのサイズ
#define FRAME_POS_X			\
(SCREEN_WIDTH/2-FRAME_SIZE_X/2)	// ポリゴンの表示位置
#define FRAME_POS_Y			\
(SCREEN_HEIGHT/2-FRAME_SIZE_Y/2)// ポリゴンの表示位置

#define SCORE_WIDTH			8								// 表示桁数
#define SCORE_SIZE_X		35								// 文字のサイズ
#define SCORE_SIZE_Y		50								// 文字のサイズ
#define SCORE_POS_X			\
(FRAME_POS_X-SCORE_SIZE_X*(SCORE_WIDTH/2))// 文字の表示位置
#define SCORE_POS_Y			\
(FRAME_POS_Y+SCORE_SIZE_Y/2-8)	// 文字の表示位置

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static int							g_nScore;
static XMFLOAT2						g_vPos =
	XMFLOAT2(SCORE_POS_X, SCORE_POS_Y);

//=============================================================================
// スコア表示の初期化処理
//=============================================================================
HRESULT InitScore()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		FRAME_TEXTURENAME, &g_pTexture);

	// スコア初期化
	g_nScore = 0;

	return hr;
}

//=============================================================================
// スコア表示の終了処理
//=============================================================================
void UninitScore()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// スコア表示の更新処理
//=============================================================================
void UpdateScore()
{
	// (何もしない)
}

//=============================================================================
// スコア表示処理
//=============================================================================
void DrawScore()
{
	ID3D11DeviceContext* pDeviceContext =
		GetDeviceContext();

	// 全体を明るい緑で表示
	SetPolygonColor(0.0f, 1.0f, 0.0f);

	// スコア枠描画
	SetPolygonPos(FRAME_POS_X, FRAME_POS_Y);
	SetPolygonSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDeviceContext);

	// スコア表示
	DrawNumber(&g_vPos,
		(unsigned)g_nScore, SCORE_WIDTH);

	// 色を元に戻す
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}

//=============================================================================
// スコア加算
//=============================================================================
void AddScore(int nValue)
{
	g_nScore += nValue;
}

//=============================================================================
// スコア取得
//=============================================================================
int GetScore()
{
	return g_nScore;
}
