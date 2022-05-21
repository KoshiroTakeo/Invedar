//=============================================================================
//
// �e���� [bullet.cpp]
// Author : Takeo
//
//=============================================================================
#include "bullet.h"
#include "polygon.h"
#include "Texture.h"
#include "enemy.h"
#include "player.h"
#include "tohchica.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static Bullet cEnemyBullet[ENEMY_BULLET_MAX];
static Bullet cPlayerBullet[PLAYER_BULLET_MAX];
static bool g_bPlayer_InterbalFire; //Player�p���˃t���O



//*****************************************************************************
// �R���X�g���N�^�Ńw�b�_�[���g��ʂ�悤�ɂ���?
//*****************************************************************************
Bullet::Bullet() {}


//=============================================================================
// �e�̏���������
//=============================================================================
void Bullet::Init()
{
	//PrintDebugProc("Bullet Init\n");

	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		BULLET_TEXTURENAME, &g_pTexture);

	cEnemyBullet->Init_EnemyBullet();
	cPlayerBullet->Init_PlayerBullet();

}


//=============================================================================
// �e�̏I������
//=============================================================================
void Bullet::Uninit()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}


//=============================================================================
// �e�̍X�V����
//=============================================================================
void Bullet::Update()
{
	//PrintDebugProc("Bullet Update\n");


	Enemy cEnemy;
	Player cPlayer;
	Tohchica cTohchica;

	Bullet* pEnemyBullet  = cEnemyBullet;
	Bullet* pPlayerBullet = cPlayerBullet;



	//�v���C���[�̒e 
	for (int i = 0; i < PLAYER_BULLET_MAX; ++i, ++pPlayerBullet)
	{
		if (pPlayerBullet->m_bFire == true)
		{
			//PrintDebugProc("%d\n" , pPlayerBullet->m_fPosition.y);
			pPlayerBullet->m_fPosition.y += BULLET_MOVE_SPEED;

			// �e�ƓG�̐ڐG����
			if (pPlayerBullet->m_fPosition.y >= pPlayerBullet->m_fMaxPos || cEnemy.CollisionEnemy(pPlayerBullet->m_fPosition.x, 
				pPlayerBullet->m_fPosition.y, pPlayerBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pPlayerBullet->m_bFire = false;
				cPlayerBullet->m_fPosition = PLAYER_BULLET_DEFULT_POS;
			}

			// �e�ƃg�[�`�J�̐ڐG����
			if (pPlayerBullet->m_fPosition.y >= pPlayerBullet->m_fMaxPos || cTohchica.CollisionTohchica(pPlayerBullet->m_fPosition.x,
				pPlayerBullet->m_fPosition.y, pPlayerBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pPlayerBullet->m_bFire = false;
				cPlayerBullet->m_fPosition = PLAYER_BULLET_DEFULT_POS;
			}
		}
	}



	//�G�̒e
	for (int i = 0; i < ENEMY_BULLET_MAX; ++i, ++pEnemyBullet)
	{
		if (pEnemyBullet->m_bFire == true)
		{
			//PrintDebugProc("%d\n" , pEnemyBullet->m_fPosition.y);
			pEnemyBullet->m_fPosition.y -= BULLET_MOVE_SPEED;

			// �e�ƃv���C���[�̐ڐG����
			if (pEnemyBullet->m_fPosition.y <= -pEnemyBullet->m_fMaxPos || 
				cPlayer.CollisionPlayer(pEnemyBullet->m_fPosition.x, pEnemyBullet->m_fPosition.y, pEnemyBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pEnemyBullet->m_bFire = false;
				pEnemyBullet->m_fPosition = ENEMY_BULLET_DEFULT_POS;
				//PrintDebugProc("EnemyBullet Start\n");
			}

			//�e�ƃg�[�`�J�̐ڐG����
			if (pEnemyBullet->m_fPosition.y <= -pEnemyBullet->m_fMaxPos ||
				cTohchica.CollisionTohchica(pEnemyBullet->m_fPosition.x, pEnemyBullet->m_fPosition.y, pEnemyBullet->m_fSize.x, 0, 0, 0) >= 0)
			{
				pEnemyBullet->m_bFire = false;
				pEnemyBullet->m_fPosition = ENEMY_BULLET_DEFULT_POS;
				//PrintDebugProc("EnemyBullet Start\n");
			}

		}

	}

}


//=============================================================================
// �e�̕`�揈��
//=============================================================================
void Bullet::Draw()
{
	//PrintDebugProc("Bullet Draw\n");

	Bullet* pEnemyBullet = cEnemyBullet;
	Bullet* pPlayerBullet = cPlayerBullet;

	SetPolygonSize(BULLET_SIZE.x, BULLET_SIZE.y);
	SetPolygonTexture(g_pTexture);

	
	// �v���C���[�e�`��
	for (int i = 0; i < PLAYER_BULLET_MAX; ++i, ++pPlayerBullet)
	{
		SetPolygonPos(pPlayerBullet->m_fPosition.x, pPlayerBullet->m_fPosition.y);
		DrawPolygon(GetDeviceContext());
	}


	// �G�e�`��
	for (int i = 0; i < ENEMY_BULLET_MAX; ++i, ++pEnemyBullet)
	{
		SetPolygonPos(pEnemyBullet->m_fPosition.x, pEnemyBullet->m_fPosition.y);
		DrawPolygon(GetDeviceContext());
	}
}


//=============================================================================
// �e�̔��ˏ���
//=============================================================================
int Bullet::FireBullet(XMFLOAT2 pos, int nWho)
{
	Bullet* pPlayerBullet = cPlayerBullet;
	Bullet* pEnemyBullet  = cEnemyBullet;
	
	
	switch (nWho)
	{
		case 1://�v���C���[�̒e
			for (int i = 0; i < PLAYER_BULLET_MAX; ++i, ++pPlayerBullet)
			{
				if (pPlayerBullet->m_bFire == false)
				{
					//PrintDebugProc("PlayerFire \n");
					pPlayerBullet->m_fPosition = pos;
					pPlayerBullet->m_bFire = true;
				}
				return i;
			}
			break;

		case 2://�G�̒e
			for (int i = 0; i < ENEMY_BULLET_MAX; ++i, ++pEnemyBullet)
			{
				if (pEnemyBullet->m_bFire == false)
				{
					//PrintDebugProc("EnemyFire \n");
					pEnemyBullet->m_fPosition = pos;
					pEnemyBullet->m_bFire = true;
				}
				return i;
			}
			break;
	}

	return -1;
}



//*****************************************************************************
// ������
//*****************************************************************************

// �G
void Bullet::Init_EnemyBullet()
{
	//�ϐ�������
	for (int i = 0; i < ENEMY_BULLET_MAX; ++i)
	{
		cEnemyBullet[i].m_fPosition = ENEMY_BULLET_DEFULT_POS;
		cEnemyBullet[i].m_fSize = BULLET_SIZE;
		cEnemyBullet[i].m_fMaxPos = DESTROY_POS;
		cEnemyBullet[i].m_bFireSwitch = 0;
		cEnemyBullet[i].m_bFire = false;
	}
	PrintDebugProc("EnemyBullet Init\n");
}

// ����
void Bullet::Init_PlayerBullet()
{
	//�ϐ�������
	for (int i = 0; i < PLAYER_BULLET_MAX; ++i)
	{
		cPlayerBullet[i].m_fPosition = PLAYER_BULLET_DEFULT_POS;
		cPlayerBullet[i].m_fSize = BULLET_SIZE;
		cPlayerBullet[i].m_fMaxPos = DESTROY_POS;
		cPlayerBullet[i].m_bFireSwitch = 0;
		cPlayerBullet[i].m_bFire = false;
	}

	PrintDebugProc("PlayerBullet Init\n");
}




//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Bullet::~Bullet() {}