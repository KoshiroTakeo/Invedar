//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================

//システム
#include "game.h"
#include "polygon.h"
#include "Texture.h"
#include "bg.h"


#include "player.h"
#include "bullet.h"
#include "tohchica.h"
#include "enemy.h"
#include "effect.h"
#include "flare.h"
#include "score.h"
#include "Sound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player c_Player;
Bullet c_Bullet;
Enemy  c_Enemy;
Tohchica c_Tohchica;


//=============================================================================
// ゲーム画面の初期化処理
//=============================================================================
HRESULT InitGame()
{
	HRESULT hr = S_OK;

	// プレイヤー初期化
	c_Player.Init();

	//敵初期化
	c_Enemy.Init();

	//トーチカ
	c_Tohchica.Init();

	// 背景表示初期化
	hr = InitBG();
	if (FAILED(hr)) {
		MsgBox(_T("背景初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// エフェクト処理初期化
	hr = InitEffect();
	if (FAILED(hr)) {
		MsgBox(_T("エフェクト処理初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// スコア表示処理初期化
	hr = InitScore();
	if (FAILED(hr)) {
		MsgBox(_T("スコア表示処理初期化エラー"), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 弾処理初期化
	c_Bullet.Init();
	

	return hr;
}

//=============================================================================
// ゲーム画面の終了処理
//=============================================================================
void UninitGame()
{
	// BGM停止
	CSound::Stop(BGM_000);
	
	// スコア表示終了処理
	UninitScore();

	// 弾終了処理
	c_Bullet.Uninit();
	
	// 背景表示終了処理
	UninitBG();

	// エフェクト終了処理
	UninitEffect();

	//トーチカ
	c_Tohchica.Uninit();

	//敵初期化
	c_Enemy.Uninit();

	// プレイヤー終了処理
	c_Player.Uninit();
	
}

//=============================================================================
// ゲーム画面の更新処理
//=============================================================================
void UpdateGame()
{
	// フェードインが完了したらBGM再生
	CSound::Play(BGM_000);
	

	// 背景表示更新
	UpdateBG();

	// プレイヤー更新
	c_Player.Update();

	//敵更新
	c_Enemy.Update();

	//トーチカ
	c_Tohchica.Update();

	// 弾更新
	c_Bullet.Update();

	// エフェクト更新
	UpdateEffect();

	// スコア更新
	UpdateScore();

	

}

//=============================================================================
// ゲーム画面処理
//=============================================================================
void DrawGame()
{
	// 背景描画処理 (必ずClearRenderTargetViewの直後)
	DrawBG();

	// 弾描画処理
	c_Bullet.Draw();

	// エフェクト描画処理
	DrawEffect();

	// プレイヤー描画処理
	c_Player.Draw();

	//敵描画
	c_Enemy.Draw();

	//トーチカ
	c_Tohchica.Draw();

	// スコア描画処理
	DrawScore();

	
}
