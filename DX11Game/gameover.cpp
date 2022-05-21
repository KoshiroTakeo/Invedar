//=============================================================================
//
// タイトル画面処理 [gameover.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "gameover.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMEOVER_TEXTURENAME	L"data/texture/gameover000.png"	// テクスチャファイル名

#define GAMEOVER_POS_X		0								// ポリゴンの表示位置
#define GAMEOVER_POS_Y		0								// ポリゴンの表示位置
#define GAMEOVER_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define GAMEOVER_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ

#define GAMEOVER_TIMER      (60*20)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ

static int g_nTimer;

//=============================================================================
// タイトル画面の初期化処理
//=============================================================================
HRESULT InitGameover()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMEOVER_TEXTURENAME, &g_pTexture);

	//タイマー初期化
	g_nTimer = GAMEOVER_TIMER;

	return hr;
}

//=============================================================================
// タイトル画面の終了処理
//=============================================================================
void UninitGameover()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// タイトル画面の更新処理
//=============================================================================
void UpdateGameover()
{
	//スペースキーを押したらゲーム開始
	if (GetKeyRelease(VK_SPACE))
	{
		//ゲーム画面へ
		SetScene(SCENE_TITLE);
	}
	g_nTimer--;
	if (g_nTimer <= 0)
	{
		//ゲーム画面へ
		SetScene(SCENE_TITLE);
	}
}

//=============================================================================
// タイトル画面処理
//=============================================================================
void DrawGameover()
{
	// 背景描画
	SetPolygonPos(GAMEOVER_POS_X, GAMEOVER_POS_Y);
	SetPolygonSize(GAMEOVER_SIZE_X, GAMEOVER_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
