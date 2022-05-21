//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================

//�V�X�e��
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
// �O���[�o���ϐ�
//*****************************************************************************
Player c_Player;
Bullet c_Bullet;
Enemy  c_Enemy;
Tohchica c_Tohchica;


//=============================================================================
// �Q�[����ʂ̏���������
//=============================================================================
HRESULT InitGame()
{
	HRESULT hr = S_OK;

	// �v���C���[������
	c_Player.Init();

	//�G������
	c_Enemy.Init();

	//�g�[�`�J
	c_Tohchica.Init();

	// �w�i�\��������
	hr = InitBG();
	if (FAILED(hr)) {
		MsgBox(_T("�w�i�������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �G�t�F�N�g����������
	hr = InitEffect();
	if (FAILED(hr)) {
		MsgBox(_T("�G�t�F�N�g�����������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �X�R�A�\������������
	hr = InitScore();
	if (FAILED(hr)) {
		MsgBox(_T("�X�R�A�\�������������G���["), MB_OK | MB_ICONSTOP);
		return hr;
	}

	// �e����������
	c_Bullet.Init();
	

	return hr;
}

//=============================================================================
// �Q�[����ʂ̏I������
//=============================================================================
void UninitGame()
{
	// BGM��~
	CSound::Stop(BGM_000);
	
	// �X�R�A�\���I������
	UninitScore();

	// �e�I������
	c_Bullet.Uninit();
	
	// �w�i�\���I������
	UninitBG();

	// �G�t�F�N�g�I������
	UninitEffect();

	//�g�[�`�J
	c_Tohchica.Uninit();

	//�G������
	c_Enemy.Uninit();

	// �v���C���[�I������
	c_Player.Uninit();
	
}

//=============================================================================
// �Q�[����ʂ̍X�V����
//=============================================================================
void UpdateGame()
{
	// �t�F�[�h�C��������������BGM�Đ�
	CSound::Play(BGM_000);
	

	// �w�i�\���X�V
	UpdateBG();

	// �v���C���[�X�V
	c_Player.Update();

	//�G�X�V
	c_Enemy.Update();

	//�g�[�`�J
	c_Tohchica.Update();

	// �e�X�V
	c_Bullet.Update();

	// �G�t�F�N�g�X�V
	UpdateEffect();

	// �X�R�A�X�V
	UpdateScore();

	

}

//=============================================================================
// �Q�[����ʏ���
//=============================================================================
void DrawGame()
{
	// �w�i�`�揈�� (�K��ClearRenderTargetView�̒���)
	DrawBG();

	// �e�`�揈��
	c_Bullet.Draw();

	// �G�t�F�N�g�`�揈��
	DrawEffect();

	// �v���C���[�`�揈��
	c_Player.Draw();

	//�G�`��
	c_Enemy.Draw();

	//�g�[�`�J
	c_Tohchica.Draw();

	// �X�R�A�`�揈��
	DrawScore();

	
}
