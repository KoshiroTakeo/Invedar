//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Takeo
//
//=============================================================================
#pragma once


//*****************************************************************************
// include
//*****************************************************************************
#include "main.h"
#include "Object.h"


//*****************************************************************************
// define
//*****************************************************************************
#define  TOHCHICA_SIZE	(XMFLOAT2(10.0f,10.0f))
#define  TOHCHICA_DEFULT_POS_CENTER (XMFLOAT2(0.0f,-100.0f))
#define  TOHCHICA_DEFULT_POS_LEFT (XMFLOAT2(-100.0f,-100.0f))
#define  TOHCHICA_DEFULT_POS_RIGHT (XMFLOAT2(100.0f,-100.0f))
#define  TOHCHICA_RADIUS 5
#define  TOHCHICA_MAX_ROWS    10 //���̍s��
#define  TOHCHICA_MAX_COLUMNS 6  //�c�̗�
#define  TOHCHICA_DISTANCE 5

#define PLAYER_TEXTURENAME	L"data/texture/inverder_Player.png"	// �e�N�X�`���t�@�C����

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Tohchica : public Object
{
public:
	Tohchica(void);
	~Tohchica(void);

	void Init();
	void Update();
	void Draw();
	void Uninit();

	int CollisionTohchica(float fX, float fY, float fR, float fDamage, float* pfX, float* pfY);



private:
	//-- �����o�ϐ� --
	int m_nDestroy;
	int m_MaxTohchica = TOHCHICA_MAX_ROWS * TOHCHICA_MAX_COLUMNS * 3;
	int m_Destroy;
	
	void Init_Tohchica();

	

};

