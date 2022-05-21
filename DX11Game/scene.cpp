//=============================================================================
//
// シーン遷移処理 [scene.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "gameover.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_nScene = SCENE_NONE;				// 現在のシーン

//=============================================================================
// シーン遷移の初期化処理
//=============================================================================
HRESULT InitScene()
{
	SetScene(SCENE_TITLE);

	return S_OK;
}

//=============================================================================
// シーン遷移の終了処理
//=============================================================================
void UninitScene()
{
	SetScene(SCENE_NONE);//現在のシーン終了
}

//=============================================================================
// シーンの更新処理
//=============================================================================
void UpdateScene()
{
	switch (g_nScene) {
	case SCENE_TITLE://タイトル画面
		UpdateTitle();
		break;
	case SCENE_GAME://ゲーム画面
		UpdateGame();
		break;
	case SCENE_GAMEOVER://ゲーム画面
		UpdateGameover();
		break;
	}
}

//=============================================================================
// シーン表示処理
//=============================================================================
void DrawScene()
{
	switch (g_nScene) {
	case SCENE_TITLE://タイトル画面
		DrawTitle();
		break;
	case SCENE_GAME://ゲーム画面
		DrawGame();
		break;
	case SCENE_GAMEOVER://ゲーム画面
		DrawGameover();
		break;
	}
}

//=============================================================================
// シーン切り替え処理
//=============================================================================
void SetScene(int nScene)
{
	//現在のシーンを終了
	switch (g_nScene) {
	case SCENE_TITLE://タイトル画面
		UninitTitle();
		break;
	case SCENE_GAME://ゲーム画面
		UninitGame();
		break;
	case SCENE_GAMEOVER://ゲーム画面
		UninitGameover();
		break;
	}
	//シーン切り替え
	g_nScene = nScene;
	//次のシーンの初期化
	switch (nScene) {
	case SCENE_TITLE://タイトル画面
		InitTitle();
		break;
	case SCENE_GAME://ゲーム画面
		InitGame();
		break;
	case SCENE_GAMEOVER://ゲーム画面
		InitGameover();
		break;
	}

}
