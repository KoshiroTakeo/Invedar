//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Takeo
//
//=============================================================================
#include "player.h"
#include "bullet.h"
#include "flare.h"
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
static Player cPlayer;


//*****************************************************************************
// �R���X�g���N�^�Ńw�b�_�[���g��ʂ�悤�ɂ���?
//*****************************************************************************
Player::Player() {}


//*****************************************************************************
// ������
//*****************************************************************************
void Player::Init()
{
	//PrintDebugProc("Player Init\n");

	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		PLAYER_TEXTURENAME, &g_pTexture);

	//�ϐ�������
	cPlayer.m_fPosition = PLAYER_DEFULT_POS;
	cPlayer.m_fSize = PLAYER_SIZE;
	cPlayer.m_fMaxPos = PLAYER_LIMITPOS;
	cPlayer.m_nLife = PLAYER_LIFE;
	
}


//*****************************************************************************
// �I��
//*****************************************************************************
void Player::Uninit()
{
	//PrintDebugProc("Player Uninit\n");
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}


//*****************************************************************************
// �X�V
//*****************************************************************************
void Player::Update()
{
	//PrintDebugProc("Player Update\n");

	//-- �L�[���͂ɂ�鑀�� --
	Player::Move();

	//���S����
	if (cPlayer.m_nLife <= 0)
	{
		SetScene(SCENE_GAMEOVER);
	}
}


//*****************************************************************************
// �`��
//*****************************************************************************
void Player::Draw()
{
	//PrintDebugProc("Player Draw\n");

	// �v���C���[�`��
	SetPolygonPos(cPlayer.m_fPosition.x, cPlayer.m_fPosition.y);
	SetPolygonSize(cPlayer.m_fSize.x, cPlayer.m_fSize.y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}


//*****************************************************************************
// ����
//*****************************************************************************
void Player::Move()
{

	if (GetKeyPress(VK_A))
	{
		if (cPlayer.m_fPosition.x >= -cPlayer.m_fMaxPos)
		{
			// ���ړ�
			PrintDebugProc("Left ON\n");
			cPlayer.m_fPosition.x -= PLAYER_MOVE_SPEED;
		}

	}
	else if (GetKeyPress(VK_D))
	{
		if (cPlayer.m_fPosition.x <= cPlayer.m_fMaxPos)
		{
			// �E�ړ�
			PrintDebugProc("Right ON\n");
			cPlayer.m_fPosition.x += PLAYER_MOVE_SPEED;
		}
	}

	Bullet cBullet;
	if (GetKeyPress(VK_SPACE))
	{
		// �e����
		PrintDebugProc("Fire \n");
		cBullet.FireBullet(cPlayer.m_fPosition , 1);
		if (!m_bInterbal)
		{
			m_bInterbal = true;
		}
	}
}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Player::~Player() {}


//*****************************************************************************
// �����蔻��
//*****************************************************************************
int Player::CollisionPlayer(float fX, float fY, float fR,
	float fDamage, float* pfX, float* pfY)
{
	Player p_cPlayer = cPlayer;
	

		// �Փ˔���
		if (CollisionCircle(p_cPlayer.m_fPosition.x, p_cPlayer.m_fPosition.y, PLAYER_RADIUS, fX, fY, fR))
		{
			// ���W��Ԃ�
			if (pfX) *pfX = p_cPlayer.m_fPosition.x;

			if (pfY) *pfY = p_cPlayer.m_fPosition.y;

			StartEffect(&p_cPlayer.m_fPosition, EEFECT_DEAD000);
			cPlayer.m_nLife--;

			return 1;	// 0�ȏ�Ȃ瓖����
		}
	
	return -1;			// �͂���
}
