//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "title.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTURENAME	L"data/texture/title000.png"	// �e�N�X�`���t�@�C����

#define TITLE_POS_X		0								// �|���S���̕\���ʒu
#define TITLE_POS_Y		0								// �|���S���̕\���ʒu
#define TITLE_SIZE_X		SCREEN_WIDTH					// �|���S���̃T�C�Y
#define TITLE_SIZE_Y		SCREEN_HEIGHT					// �|���S���̃T�C�Y

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��

//=============================================================================
// �^�C�g����ʂ̏���������
//=============================================================================
HRESULT InitTitle()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		TITLE_TEXTURENAME, &g_pTexture);

	return hr;
}

//=============================================================================
// �^�C�g����ʂ̏I������
//=============================================================================
void UninitTitle()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// �^�C�g����ʂ̍X�V����
//=============================================================================
void UpdateTitle()
{
	//�X�y�[�X�L�[����������Q�[���J�n
	if (GetKeyRelease(VK_SPACE))
	{
		//�Q�[����ʂ�
		SetScene(SCENE_GAME);
	}
}

//=============================================================================
// �^�C�g����ʏ���
//=============================================================================
void DrawTitle()
{
	// �w�i�`��
	SetPolygonPos(TITLE_POS_X, TITLE_POS_Y);
	SetPolygonSize(TITLE_SIZE_X, TITLE_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}