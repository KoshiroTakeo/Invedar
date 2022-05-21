//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Takeo
//
//=============================================================================
#include "tohchica.h"
#include "bullet.h"
#include "enemy.h"
#include "effect.h"
#include "collision.h"


//�V�X�e��
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "input.h"
#include "scene.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************




//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static Tohchica cTohchica[(TOHCHICA_MAX_ROWS * TOHCHICA_MAX_COLUMNS) * 3];


//*****************************************************************************
// �R���X�g���N�^�Ńw�b�_�[���g��ʂ�悤�ɂ���?
//*****************************************************************************
Tohchica::Tohchica() {}


//*****************************************************************************
// ������
//*****************************************************************************
void Tohchica::Init()
{
	//PrintDebugProc("Player Init\n");

	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		PLAYER_TEXTURENAME, &g_pTexture);

	//�ϐ�������
	cTohchica->Init_Tohchica();

}


//*****************************************************************************
// �I��
//*****************************************************************************
void Tohchica::Uninit()
{
	//PrintDebugProc("Player Uninit\n");
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}


//*****************************************************************************
// �X�V
//*****************************************************************************
void Tohchica::Update()
{
	//PrintDebugProc("Player Update\n");

	
}


//*****************************************************************************
// �`��
//*****************************************************************************
void Tohchica::Draw()
{
	//PrintDebugProc("Player Draw\n");
	Tohchica* pTohchica = cTohchica;

	// �v���C���[�`��
	SetPolygonPos(pTohchica->m_fPosition.x, pTohchica->m_fPosition.y);
	SetPolygonSize(pTohchica->m_fSize.x, pTohchica->m_fSize.y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());

	// �G�`��
	for (int i = 0; i < m_MaxTohchica; i++, pTohchica++)
	{
		if (pTohchica->m_nDestroy == 1) continue;

		SetPolygonPos(pTohchica->m_fPosition.x, pTohchica->m_fPosition.y);
		SetPolygonSize(pTohchica->m_fSize.x, pTohchica->m_fSize.y);

		DrawPolygon(GetDeviceContext());

	}
}

// �g�[�`�J������
void Tohchica::Init_Tohchica()
{

	int i = 0;
	int n = 0;
	int t = 0;

	for (int y = 0; y < TOHCHICA_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < TOHCHICA_MAX_ROWS; ++x, i++)
		{
			cTohchica[i].m_fPosition = TOHCHICA_DEFULT_POS_LEFT;
			cTohchica[i].m_fPosition.x += TOHCHICA_DISTANCE * x;
			cTohchica[i].m_fPosition.y += TOHCHICA_DISTANCE * y;
			cTohchica[i].m_fSize = TOHCHICA_SIZE;
			cTohchica[i].m_nDestroy = 0;
		}
	}


	for (int y = 0; y < TOHCHICA_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < TOHCHICA_MAX_ROWS; ++x, i++)
		{
			cTohchica[i].m_fPosition = TOHCHICA_DEFULT_POS_CENTER;
			cTohchica[i].m_fPosition.x += TOHCHICA_DISTANCE * x;
			cTohchica[i].m_fPosition.y += TOHCHICA_DISTANCE * y;
			cTohchica[i].m_fSize = TOHCHICA_SIZE;
			cTohchica[i].m_nDestroy = 0;
		}
	}

	for (int y = 0; y < TOHCHICA_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < TOHCHICA_MAX_ROWS; ++x, i++)
		{
			cTohchica[i].m_fPosition = TOHCHICA_DEFULT_POS_RIGHT;
			cTohchica[i].m_fPosition.x += TOHCHICA_DISTANCE * x;
			cTohchica[i].m_fPosition.y += TOHCHICA_DISTANCE * y;
			cTohchica[i].m_fSize = TOHCHICA_SIZE;
			cTohchica[i].m_nDestroy = 0;
		}
	}

	PrintDebugProc("PlayerBullet Init\n");
}



//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Tohchica::~Tohchica() {}


//*****************************************************************************
// �����蔻��
//*****************************************************************************
int Tohchica::CollisionTohchica(float fX, float fY, float fR,
	float fDamage, float* pfX, float* pfY)
{
	Tohchica* p_cTohchica = cTohchica;

	for (int i = 0; i < m_MaxTohchica; i++, p_cTohchica++)
	{
		// �Փ˔���
		if (CollisionCircle(p_cTohchica->m_fPosition.x, p_cTohchica->m_fPosition.y, TOHCHICA_RADIUS, fX, fY, fR))
		{
			// ���W��Ԃ�
			if (pfX) *pfX = p_cTohchica->m_fPosition.x;

			if (pfY) *pfY = p_cTohchica->m_fPosition.y;

			StartEffect(&p_cTohchica->m_fPosition, EEFECT_DEAD000);
			p_cTohchica->m_nDestroy = 1;

			return 1;	// 0�ȏ�Ȃ瓖����
		}
	}

	return -1;			// �͂���
}
