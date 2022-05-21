//=============================================================================
//
// �^�C�g����ʏ��� [gameover.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "gameover.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMEOVER_TEXTURENAME	L"data/texture/gameover000.png"	// �e�N�X�`���t�@�C����

#define GAMEOVER_POS_X		0								// �|���S���̕\���ʒu
#define GAMEOVER_POS_Y		0								// �|���S���̕\���ʒu
#define GAMEOVER_SIZE_X		SCREEN_WIDTH					// �|���S���̃T�C�Y
#define GAMEOVER_SIZE_Y		SCREEN_HEIGHT					// �|���S���̃T�C�Y

#define GAMEOVER_TIMER      (60*20)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��

static int g_nTimer;

//=============================================================================
// �^�C�g����ʂ̏���������
//=============================================================================
HRESULT InitGameover()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMEOVER_TEXTURENAME, &g_pTexture);

	//�^�C�}�[������
	g_nTimer = GAMEOVER_TIMER;

	return hr;
}

//=============================================================================
// �^�C�g����ʂ̏I������
//=============================================================================
void UninitGameover()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// �^�C�g����ʂ̍X�V����
//=============================================================================
void UpdateGameover()
{
	//�X�y�[�X�L�[����������Q�[���J�n
	if (GetKeyRelease(VK_SPACE))
	{
		//�Q�[����ʂ�
		SetScene(SCENE_TITLE);
	}
	g_nTimer--;
	if (g_nTimer <= 0)
	{
		//�Q�[����ʂ�
		SetScene(SCENE_TITLE);
	}
}

//=============================================================================
// �^�C�g����ʏ���
//=============================================================================
void DrawGameover()
{
	// �w�i�`��
	SetPolygonPos(GAMEOVER_POS_X, GAMEOVER_POS_Y);
	SetPolygonSize(GAMEOVER_SIZE_X, GAMEOVER_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
