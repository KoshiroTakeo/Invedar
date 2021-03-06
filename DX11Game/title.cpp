//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "title.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTURENAME	L"data/texture/title000.png"	// テクスチャファイル名

#define TITLE_POS_X		0								// ポリゴンの表示位置
#define TITLE_POS_Y		0								// ポリゴンの表示位置
#define TITLE_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define TITLE_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ

//=============================================================================
// タイトル画面の初期化処理
//=============================================================================
HRESULT InitTitle()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		TITLE_TEXTURENAME, &g_pTexture);

	return hr;
}

//=============================================================================
// タイトル画面の終了処理
//=============================================================================
void UninitTitle()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// タイトル画面の更新処理
//=============================================================================
void UpdateTitle()
{
	//スペースキーを押したらゲーム開始
	if (GetKeyRelease(VK_SPACE))
	{
		//ゲーム画面へ
		SetScene(SCENE_GAME);
	}
}

//=============================================================================
// タイトル画面処理
//=============================================================================
void DrawTitle()
{
	// 背景描画
	SetPolygonPos(TITLE_POS_X, TITLE_POS_Y);
	SetPolygonSize(TITLE_SIZE_X, TITLE_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
