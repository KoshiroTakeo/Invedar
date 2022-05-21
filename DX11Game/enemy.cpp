//=============================================================================
//
// �G���� [enemy.cpp]
// Author : Takeo
//
//=============================================================================
#include "enemy.h"
#include "collision.h"
#include "score.h"
#include "bullet.h"
#include "flare.h"
#include "effect.h"


//�V�X�e��
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
// �\����
//*****************************************************************************



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static Enemy cEnemy[ENEMY_SPOWN_MAX_ROWS * ENEMY_SPOWN_MAX_COLUMNS];

static float g_Timer;
static int g_RimitTimer;
static float g_nTopPos;



//*****************************************************************************
// �R���X�g���N�^�Ńw�b�_�[���g��ʂ�悤�ɂ���?
//*****************************************************************************
Enemy::Enemy() {}



//*****************************************************************************
// ������
//*****************************************************************************
void Enemy::Init()
{
	//PrintDebugProc("Enemy Init\n");

	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMY_TEXTURENAME, &g_pTexture);

	//�ϐ�������
	cEnemy->Init_Enemy();

	g_Timer = 0.0f;
	g_RimitTimer = 60.0f;

	

	
	m_Down = false;
	
}



//*****************************************************************************
// �I��
//*****************************************************************************
void Enemy::Uninit()
{
	//PrintDebugProc("Enemy Uninit\n");
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);

	//�ϐ�������
	//Enemy* p_cEnemy = cEnemy;
}



//*****************************************************************************
// �X�V
//*****************************************************************************
void Enemy::Update()
{
	//PrintDebugProc("Enemy Update\n");

	//�ϐ�������
	Enemy* p_cEnemy = cEnemy;
	Bullet* cBullet = new Bullet();

	//�����ۑ��p
	int randSave;

	//���ԃJ�E���g
	g_Timer++;
	
	
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		//�e�������_���ɔ���
		if (p_cEnemy[randSave = rand() % m_MaxEnemy].m_Destroy == 0)
		{
			cBullet->FireBullet(p_cEnemy[randSave].m_fPosition, 2);
		}
		


		//���ł������ɂ��s���X�s�[�h���グ��
		if (p_cEnemy->m_Destroy == 1 && p_cEnemy->m_CountCheck == false)
		{
			g_RimitTimer *= 0.98;
			p_cEnemy->m_CountCheck = true;
		}
		


		//g_nTimer���P�ȉ��̎��̂݁A���̍s�����N����
		if (g_Timer >= g_RimitTimer)
		{
			//���֍~���
			if (p_cEnemy->m_Destroy == 1)continue;
			if (p_cEnemy->m_fPosition.x >= ENEMY_LIMITPOS)
			{
				PosDownR();
				p_cEnemy->m_Turn = true;
			}
			else if (p_cEnemy->m_fPosition.x <= -ENEMY_LIMITPOS)
			{
				PosDownL();
				p_cEnemy->m_Turn = false;
			}

			//�ړ��̐܂�Ԃ�
			if (m_Down)
			{
				MoveR();
			}
			else if (!m_Down)
			{
				MoveL();
			}

			g_Timer = 0;

		}
	}
}



//*****************************************************************************
// �`��
//*****************************************************************************
void Enemy::Draw()
{
	//PrintDebugProc("Enemy Draw\n");

	SetPolygonTexture(g_pTexture);

	//�ϐ�������
	Enemy* p_cEnemy = cEnemy;
	
	// �G�`��
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		if (p_cEnemy->m_Destroy == 1) continue;

		SetPolygonPos(p_cEnemy->m_fPosition.x, p_cEnemy->m_fPosition.y);
		SetPolygonSize(p_cEnemy->m_fSize.x, p_cEnemy->m_fSize.y);
		
		DrawPolygon(GetDeviceContext());

		//PrintDebugProc("Init Enemy NO_%f\n", i);
	}
	
}



//*****************************************************************************
// �Q�̂̉��~����
//*****************************************************************************
void Enemy::PosDownR()
{
	//�ϐ�������
	Enemy* p_cEnemy = cEnemy;

	
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		
		if (m_Down) continue;
		p_cEnemy->m_fPosition.y -= ENEMY_DISTANCE;	
	}
	
	m_Down = true;
}

void Enemy::PosDownL()
{
	//�ϐ�������
	Enemy* p_cEnemy = cEnemy;


	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		
		if (!m_Down) continue;
		p_cEnemy->m_fPosition.y -= ENEMY_DISTANCE;
	}

	m_Down = false;
}



//*****************************************************************************
// �Q�̂̈ړ�����
//*****************************************************************************
void Enemy::MoveR()
{
	//�ϐ�������
	Enemy* p_cEnemy = cEnemy;


	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		if (p_cEnemy->m_Destroy == 0) 
		p_cEnemy->m_fPosition.x -= ENEMY_MOVE_SPEED;
	}
}

void Enemy::MoveL()
{
	//�ϐ�������
	Enemy* p_cEnemy = cEnemy;


	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++)
	{
		if (p_cEnemy->m_Destroy == 0)
		p_cEnemy->m_fPosition.x += ENEMY_MOVE_SPEED;
	}
}




//*****************************************************************************
// �G������
//*****************************************************************************
void Enemy::Init_Enemy()
{
	int i = 0;

	for (int y = 0; y < ENEMY_SPOWN_MAX_COLUMNS; ++y)
	{
		for (int x = 0; x < ENEMY_SPOWN_MAX_ROWS; ++x, i++)
		{
			//�ϐ�������
			cEnemy[i].m_fPosition = ENEMY_DEFULT_POS;
			cEnemy[i].m_fPosition.x += ENEMY_DISTANCE * x;
			cEnemy[i].m_fPosition.y += ENEMY_DISTANCE * -y;
			cEnemy[i].m_fSize = ENEMY_SIZE;
			cEnemy[i].m_fMaxPos = ENEMY_LIMITPOS;
			cEnemy[i].m_Destroy = 0;
			cEnemy[i].m_CountCheck = false;
			cEnemy[i].m_Shot = false;
			cEnemy[i].m_Turn = false;
		}
	}
}


//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
Enemy::~Enemy() {}



//*****************************************************************************
// �����蔻��
//*****************************************************************************
int Enemy::CollisionEnemy(float fX, float fY, float fR,
	float fDamage, float* pfX, float* pfY)
{
	Enemy* p_cEnemy = cEnemy;
	for (int i = 0; i < m_MaxEnemy; i++, p_cEnemy++) 
	{

		// �����Ȃ�X�L�b�v
		if (p_cEnemy->m_Destroy == 1) continue;

		// �Փ˔���
		if (CollisionCircle(p_cEnemy->m_fPosition.x,p_cEnemy->m_fPosition.y, ENEMY_RADIUS, fX, fY, fR)) 
		{
			// ���W��Ԃ�
			if (pfX) *pfX = p_cEnemy->m_fPosition.x;
			
			if (pfY) *pfY = p_cEnemy->m_fPosition.y;
			

			
				p_cEnemy->m_Destroy = 1;
				StartEffect(&p_cEnemy->m_fPosition, EEFECT_DEAD000);
				AddScore(100);
			
			return i;	// 0�ȏ�Ȃ瓖����
		}
	}
	return -1;			// �͂���
}




