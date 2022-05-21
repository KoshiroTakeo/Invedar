//=============================================================================
//
// �V�[���J�ڏ��� [scene.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "gameover.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_nScene = SCENE_NONE;				// ���݂̃V�[��

//=============================================================================
// �V�[���J�ڂ̏���������
//=============================================================================
HRESULT InitScene()
{
	SetScene(SCENE_TITLE);

	return S_OK;
}

//=============================================================================
// �V�[���J�ڂ̏I������
//=============================================================================
void UninitScene()
{
	SetScene(SCENE_NONE);//���݂̃V�[���I��
}

//=============================================================================
// �V�[���̍X�V����
//=============================================================================
void UpdateScene()
{
	switch (g_nScene) {
	case SCENE_TITLE://�^�C�g�����
		UpdateTitle();
		break;
	case SCENE_GAME://�Q�[�����
		UpdateGame();
		break;
	case SCENE_GAMEOVER://�Q�[�����
		UpdateGameover();
		break;
	}
}

//=============================================================================
// �V�[���\������
//=============================================================================
void DrawScene()
{
	switch (g_nScene) {
	case SCENE_TITLE://�^�C�g�����
		DrawTitle();
		break;
	case SCENE_GAME://�Q�[�����
		DrawGame();
		break;
	case SCENE_GAMEOVER://�Q�[�����
		DrawGameover();
		break;
	}
}

//=============================================================================
// �V�[���؂�ւ�����
//=============================================================================
void SetScene(int nScene)
{
	//���݂̃V�[�����I��
	switch (g_nScene) {
	case SCENE_TITLE://�^�C�g�����
		UninitTitle();
		break;
	case SCENE_GAME://�Q�[�����
		UninitGame();
		break;
	case SCENE_GAMEOVER://�Q�[�����
		UninitGameover();
		break;
	}
	//�V�[���؂�ւ�
	g_nScene = nScene;
	//���̃V�[���̏�����
	switch (nScene) {
	case SCENE_TITLE://�^�C�g�����
		InitTitle();
		break;
	case SCENE_GAME://�Q�[�����
		InitGame();
		break;
	case SCENE_GAMEOVER://�Q�[�����
		InitGameover();
		break;
	}

}
