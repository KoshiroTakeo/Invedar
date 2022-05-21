//=============================================================================
//
// �X�R�A�\������ [score.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "score.h"
#include "polygon.h"
#include "Texture.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FRAME_TEXTURENAME	L"data/texture/frame_score.png"	// �e�N�X�`���t�@�C����

#define FRAME_SIZE_X		340								// �|���S���̃T�C�Y
#define FRAME_SIZE_Y		80								// �|���S���̃T�C�Y
#define FRAME_POS_X			\
(SCREEN_WIDTH/2-FRAME_SIZE_X/2)	// �|���S���̕\���ʒu
#define FRAME_POS_Y			\
(SCREEN_HEIGHT/2-FRAME_SIZE_Y/2)// �|���S���̕\���ʒu

#define SCORE_WIDTH			8								// �\������
#define SCORE_SIZE_X		35								// �����̃T�C�Y
#define SCORE_SIZE_Y		50								// �����̃T�C�Y
#define SCORE_POS_X			\
(FRAME_POS_X-SCORE_SIZE_X*(SCORE_WIDTH/2))// �����̕\���ʒu
#define SCORE_POS_Y			\
(FRAME_POS_Y+SCORE_SIZE_Y/2-8)	// �����̕\���ʒu

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static int							g_nScore;
static XMFLOAT2						g_vPos =
	XMFLOAT2(SCORE_POS_X, SCORE_POS_Y);

//=============================================================================
// �X�R�A�\���̏���������
//=============================================================================
HRESULT InitScore()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		FRAME_TEXTURENAME, &g_pTexture);

	// �X�R�A������
	g_nScore = 0;

	return hr;
}

//=============================================================================
// �X�R�A�\���̏I������
//=============================================================================
void UninitScore()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// �X�R�A�\���̍X�V����
//=============================================================================
void UpdateScore()
{
	// (�������Ȃ�)
}

//=============================================================================
// �X�R�A�\������
//=============================================================================
void DrawScore()
{
	ID3D11DeviceContext* pDeviceContext =
		GetDeviceContext();

	// �S�̂𖾂邢�΂ŕ\��
	SetPolygonColor(0.0f, 1.0f, 0.0f);

	// �X�R�A�g�`��
	SetPolygonPos(FRAME_POS_X, FRAME_POS_Y);
	SetPolygonSize(FRAME_SIZE_X, FRAME_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(pDeviceContext);

	// �X�R�A�\��
	DrawNumber(&g_vPos,
		(unsigned)g_nScore, SCORE_WIDTH);

	// �F�����ɖ߂�
	SetPolygonColor(1.0f, 1.0f, 1.0f);
}

//=============================================================================
// �X�R�A���Z
//=============================================================================
void AddScore(int nValue)
{
	g_nScore += nValue;
}

//=============================================================================
// �X�R�A�擾
//=============================================================================
int GetScore()
{
	return g_nScore;
}
